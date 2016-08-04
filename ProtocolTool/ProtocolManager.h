////*************************************************************************
// ProtocolManager.h 2016-8-4 16:06
// Author: Stonexin
// Purpose: 
//
//*************************************************************************


#include <string>
#include <vector>
#include <memory>

#include <google/protobuf/descriptor.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/tokenizer.h>
#include <google/protobuf/compiler/parser.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/compiler/importer.h>

#include "SingletonTemplate.h"

using namespace std;

using namespace  google::protobuf;
using namespace google::protobuf::compiler;

typedef std::shared_ptr<google::protobuf::Message> MessagePtr;


struct  MsgField
{
	std::string name;	//field name
	int type;			//the type like the double\int\string\message\bytes
	int cpp_type;		//almost like the type
	int label_type;		//optional=1 // required=2 // repeated=3
};


struct MsgInfo
{
	std::string msg_name;			//msg full name
	std::vector<MsgField> fields;
};

typedef std::shared_ptr<MsgInfo> MsgInfoPtr;

class ProtocolManager : public SingletonTpl<ProtocolManager>
{
public:
	ProtocolManager();
	~ProtocolManager();
		
	bool InitProtocol( const std::string& strProtocolDir );

	bool HandleProtocolMsg( const char * buffer, size_t size );

	MessagePtr MakeProtocolMsg( const std::string& proto_full_filename,	const std::string& strMsgName);

	MessagePtr MakeProtocolMsg(const std::string& strMsgName);

	MessagePtr FillProtoMsg(const std::string& proto_full_filename,
		const std::string& strMsgName,
		const std::vector<std::string>& fieldVals);

	MessagePtr FillProtoMsg(const std::string& strMsgName,const std::vector<std::string>& fieldVals);
	
	std::vector<std::string> GetProtocolMessageList( const std::string& proto_full_filename );

	bool GetProtoFullFileName(const std::string& protoFn,std::string& proto_full_filename);

	MsgInfo GetProtoMessageInfo(const std::string& proto_full_filename,	const std::string& strMsgName);
	
	std::vector<std::string> GetProtocolsFromDir(const std::string& dirName);

	bool GetFieldsFromProtoFile(const string& msgFullName, std::vector<MsgField>& fields);

	wxString GetProtoFullNameFromMsgName(const std::string& strMsgName);
private:

	bool MakeInputsBeProtoPathRelative(DiskSourceTree* source_tree, std::string& protoFile);
	
	bool GetDescFromProtoFile(const string& proto_full_filename, FileDescriptorProto* file_desc_proto);

	bool GetMsgListFromProtoFile(const string& proto_full_filename, std::vector<std::string>& msgNameList);

	bool GetFieldsFromProtoFile(const string& proto_full_filename,const string& msgName, std::vector<MsgField>& fields);

private:
	std::map<wxString,std::vector<MsgInfoPtr> >  m_xMessageMap;

	DiskSourceTree	m_DiskSourceTree;
	std::shared_ptr<Importer>		m_pImporter;
	DynamicMessageFactory m_DMsgFactory;
};
