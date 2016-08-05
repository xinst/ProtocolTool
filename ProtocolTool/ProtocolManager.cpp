#include "stdwx.h"
#include "ProtocolManager.h"
#include <iostream>
#include <wx/dir.h>

using namespace google::protobuf;
using namespace google::protobuf::io;
using namespace google::protobuf::compiler;


const char * const ProtocolManager::PBLabelName[4] = {
	"ERROR",     // 0 is reserved for errors

	"optional",  // LABEL_OPTIONAL
	"required",  // LABEL_REQUIRED
	"repeated",  // LABEL_REPEATED
};

ProtocolManager::ProtocolManager()
	:m_pImporter(nullptr)
{
}


ProtocolManager::~ProtocolManager()
{
}

bool ProtocolManager::InitProtocol(const std::string& strProtocolDir)
{
	m_DiskSourceTree.MapPath("", strProtocolDir);

	wxDir dir(strProtocolDir);

	wxArrayString fileList;
	dir.GetAllFiles(strProtocolDir,&fileList,wxString("*.proto"),wxDIR_FILES);//get files only

	for (size_t i = 0; i < fileList.size(); i++)
	{
		std::string proto_full_fn = fileList.Item(i);
		
		std::vector<MsgInfoPtr> msgList;

		std::vector<std::string> msgNames;
		GetMsgListFromProtoFile(proto_full_fn, msgNames);

		for (int i = 0; i < msgNames.size(); i++)
		{
			MsgInfoPtr msgInfo(new MsgInfo);
			msgInfo->msg_name = msgNames.at(i);
			GetFieldsFromProtoFile(proto_full_fn, msgInfo->msg_name, msgInfo->fields);

			msgList.push_back(msgInfo);
		}
		m_xMessageMap.emplace(proto_full_fn, msgList);
	}

	m_pImporter.reset(new Importer(&m_DiskSourceTree, NULL));

	return true;
}

MessagePtr ProtocolManager::MakeProtocolMsg(const std::string& proto_full_filename,
	const std::string& strMsgName)
{
	std::string strProtoFn = proto_full_filename;

	MakeInputsBeProtoPathRelative(&m_DiskSourceTree, strProtoFn);
	MessagePtr pMsg;
	const FileDescriptor* parsed_file = m_pImporter->Import(strProtoFn);
	int nMsgCnt = parsed_file->message_type_count();
	for (int i = 0; i < nMsgCnt; i++)
	{
		const Descriptor* pMsgDesc = parsed_file->message_type(i);
		std::string name = pMsgDesc->full_name();
		if (name == strMsgName)
		{
			const Message *pEmptyMessage = m_DMsgFactory.GetPrototype(pMsgDesc);
			pMsg.reset(pEmptyMessage->New());
			return pMsg;
		}
	}

	return pMsg;
}

MessagePtr ProtocolManager::MakeProtocolMsg(const std::string& strMsgName)
{
	wxString fullProtoName = GetProtoFullNameFromMsgName(strMsgName);
	if (fullProtoName.empty())
	{
		return MessagePtr();
	}

	return MakeProtocolMsg(fullProtoName.ToStdString(),strMsgName);
}

MessagePtr ProtocolManager::FillProtoMsg(const std::string& proto_full_filename,
	const std::string& strMsgName,
	const std::vector<std::string>& fieldVals)
{

	std::string strProtoFn = proto_full_filename;

	MakeInputsBeProtoPathRelative(&m_DiskSourceTree, strProtoFn);
	MessagePtr pRealMsg;
	const FileDescriptor* parsed_file = m_pImporter->Import(strProtoFn);
	int nMsgCnt = parsed_file->message_type_count();
	for (int i = 0; i < nMsgCnt; i++)
	{
		const Descriptor* pMsgDesc = parsed_file->message_type(i);
		std::string name = pMsgDesc->full_name();
		if (name == strMsgName)
		{
			const Message *pEmptyMessage = m_DMsgFactory.GetPrototype(pMsgDesc);
			pRealMsg.reset(pEmptyMessage->New());

			const Reflection *reflection = pRealMsg->GetReflection();

			const FieldDescriptor *field = NULL;
			int nCnt = pMsgDesc->field_count();
			for (int n = 0; n < nCnt; n++)
			{
				std::string strFieldName = pMsgDesc->field(n)->name();
				std::string strFieldValue = fieldVals.at(n);

				field = pMsgDesc->FindFieldByName(strFieldName);
								
				const int cppType = pMsgDesc->field(n)->cpp_type();
				switch (cppType)
				{
				case FieldDescriptor::CPPTYPE_BOOL:
				{
					reflection->SetBool(pRealMsg.get(), field, (strFieldValue.compare("true") == 0) ? true : false);
				}
				break;
				case FieldDescriptor::CPPTYPE_UINT32:
				{
					uint32 nValue = atol(strFieldValue.c_str());
					if (pMsgDesc->field(n)->label()==FieldDescriptor::Label::LABEL_REPEATED)
					{
						reflection->AddUInt32(pRealMsg.get(), field,nValue);
					}
					else
					{
						reflection->SetUInt32(pRealMsg.get(), field, nValue);
					}
				}
				break;
				case FieldDescriptor::CPPTYPE_UINT64:
				{
					uint64 nValue = atoll(strFieldValue.c_str());
					if (pMsgDesc->field(n)->label() == FieldDescriptor::Label::LABEL_REPEATED)
					{
						reflection->AddUInt64(pRealMsg.get(),field,nValue);
						//reflection->SetRepeatedUInt64(pRealMsg, field, 0, nValue);
					}
					else
					{
						reflection->SetUInt64(pRealMsg.get(), field, nValue);
					}
				}
				break;
				case FieldDescriptor::CPPTYPE_STRING:
				{
					reflection->SetString(pRealMsg.get(), field, strFieldValue);
				}
				break;
				case FieldDescriptor::CPPTYPE_ENUM:
				case FieldDescriptor::CPPTYPE_MESSAGE:
				case FieldDescriptor::CPPTYPE_DOUBLE:
				case FieldDescriptor::CPPTYPE_FLOAT:
				case FieldDescriptor::CPPTYPE_INT32:
				case FieldDescriptor::CPPTYPE_INT64:
					{
						return nullptr;
					}
					break;
				default:
					break;
				}
			}

			return pRealMsg;
		}
	}

	return pRealMsg;
}

MessagePtr ProtocolManager::FillProtoMsg(const std::string& strMsgName, const std::vector<std::string>& fieldVals)
{
	wxString fullProtoName = GetProtoFullNameFromMsgName(strMsgName);
	if (fullProtoName.empty())
	{
		return MessagePtr();
	}
	return FillProtoMsg(fullProtoName.ToStdString(),strMsgName,fieldVals);
}


bool ProtocolManager::MakeInputsBeProtoPathRelative(DiskSourceTree* source_tree, std::string& protoFile)
{
	string virtual_file, shadowing_disk_file;
	switch (source_tree->DiskFileToVirtualFile(
		protoFile, &virtual_file, &shadowing_disk_file))
	{
	case DiskSourceTree::SUCCESS:
		protoFile = virtual_file;
		break;
	case DiskSourceTree::SHADOWED:
		return false;
	case DiskSourceTree::CANNOT_OPEN:
		return false;
	case DiskSourceTree::NO_MAPPING:
		return false;
	}
	return true;
}

bool ProtocolManager::GetMsgListFromProtoFile(const string& proto_full_filename, std::vector<std::string>& msgNameList)
{
	std::string protoFileName = proto_full_filename;
	MakeInputsBeProtoPathRelative(&m_DiskSourceTree,protoFileName);

	Importer ip(&m_DiskSourceTree, NULL);
	const FileDescriptor* parsed_file = ip.Import(protoFileName);

	int nMsgCnt = parsed_file->message_type_count();
	for (int i = 0; i < nMsgCnt; i++)
	{
		const Descriptor* message_desc = parsed_file->message_type(i);
		std::string msgName = message_desc->full_name();
		msgNameList.push_back(msgName);
	}
	return true;
}

bool ProtocolManager::GetFieldsFromProtoFile(const string& proto_full_filename, const string& msgName, std::vector<MsgField>& fields)
{
	std::string protoFileName = proto_full_filename;
	MakeInputsBeProtoPathRelative(&m_DiskSourceTree, protoFileName);

	Importer ip(&m_DiskSourceTree, NULL);
	const FileDescriptor* parsed_file = ip.Import(protoFileName);
	if (parsed_file==nullptr)
	{
		return false;
	}

	int nMsgCnt = parsed_file->message_type_count();
	for (int i = 0; i < nMsgCnt; i++)
	{
		const Descriptor* message_desc = parsed_file->message_type(i);
		std::string tmp = message_desc->full_name();
		if(tmp==msgName)
		{
			int nCnt = message_desc->field_count();
			for (int n = 0; n < nCnt; n++)
			{
				MsgField field;
				const FieldDescriptor* pField = message_desc->field(n);
				if (pField)
				{
					field.name = pField->name();
					field.nFieldType = pField->type();
					field.label_type = pField->label();

					field.strFieldType = pField->type_name();
					field.strLabelType = PBLabelName[pField->label()];
					fields.push_back(field);
				}
			}
		}	
	}

	return true;
}

bool ProtocolManager::GetFieldsFromProtoFile(const string& strMsgName, std::vector<MsgField>& fields)
{
	std::map<wxString, std::vector<MsgInfoPtr> >::iterator it = m_xMessageMap.begin();
	while (it != m_xMessageMap.end())
	{
		std::vector<MsgInfoPtr>::iterator vIt = it->second.begin();
		while (vIt != it->second.end())
		{
			if ((*vIt)->msg_name == strMsgName)
			{
				fields = (*vIt)->fields;
				return true;
			}
			vIt++;
		}
		it++;
	}

	return false;
}

wxString ProtocolManager::GetProtoFullNameFromMsgName(const std::string& strMsgName)
{
	std::map<wxString, std::vector<MsgInfoPtr> >::iterator it = m_xMessageMap.begin();
	while (it != m_xMessageMap.end())
	{
		std::vector<MsgInfoPtr>::iterator vIt = it->second.begin();
		while (vIt != it->second.end())
		{
			if ((*vIt)->msg_name == strMsgName)
			{
				return it->first;
			}
			vIt++;
		}
		it++;
	}
	return wxString();
}

std::vector<std::string> ProtocolManager::GetProtocolMessageList( const std::string& proto_full_filename )
{
	std::vector<std::string> msgList;

	if (proto_full_filename.empty())
	{
		std::map<wxString, std::vector<MsgInfoPtr> >::iterator it = m_xMessageMap.begin();
		while(it != m_xMessageMap.end())
		{
			size_t nSize = it->second.size();
			for (size_t n = 0; n < nSize; n++)
			{
				msgList.push_back(it->second.at(n)->msg_name);
			}
			it++;
		}
	}
	else
	{
		std::map<wxString, std::vector<MsgInfoPtr> >::iterator it = m_xMessageMap.find(wxString(proto_full_filename));
		if (it != m_xMessageMap.end())
		{
			size_t nSize = it->second.size();
			for (size_t n = 0; n < nSize; n++)
			{
				msgList.push_back(it->second.at(n)->msg_name);
			}
		}
	}

	return msgList;
}

MsgInfo ProtocolManager::GetProtoMessageInfo(const std::string& proto_full_filename, const std::string& strMsgName)
{
	std::map<wxString, std::vector<MsgInfoPtr> >::iterator it = m_xMessageMap.find(wxString(proto_full_filename));
	if (it != m_xMessageMap.end())
	{
		for (size_t i = 0; i < it->second.size(); i++)
		{
			std::string msg_name = it->second.at(i)->msg_name;
			if (strMsgName == msg_name)
			{
				return *(it->second.at(i));
			}
		}
	}	
	return MsgInfo();
}

MsgInfo ProtocolManager::GetProtoMessageInfo(const string& msgFullName)
{
	wxString strFullProtoName = GetProtoFullNameFromMsgName(msgFullName);
	return GetProtoMessageInfo(strFullProtoName.ToStdString(),msgFullName);
}