// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CommGameMsg.proto

#ifndef PROTOBUF_CommGameMsg_2eproto__INCLUDED
#define PROTOBUF_CommGameMsg_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace SGFMsg {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_CommGameMsg_2eproto();
void protobuf_AssignDesc_CommGameMsg_2eproto();
void protobuf_ShutdownFile_CommGameMsg_2eproto();

class AckEventResult;
class AccountLoginReq;
class AccountLoginRes;
class EnterPlazaReq;

// ===================================================================

class AckEventResult : public ::google::protobuf::Message {
 public:
  AckEventResult();
  virtual ~AckEventResult();

  AckEventResult(const AckEventResult& from);

  inline AckEventResult& operator=(const AckEventResult& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const AckEventResult& default_instance();

  void Swap(AckEventResult* other);

  // implements Message ----------------------------------------------

  AckEventResult* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AckEventResult& from);
  void MergeFrom(const AckEventResult& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 evt_code = 1;
  inline bool has_evt_code() const;
  inline void clear_evt_code();
  static const int kEvtCodeFieldNumber = 1;
  inline ::google::protobuf::int32 evt_code() const;
  inline void set_evt_code(::google::protobuf::int32 value);

  // optional int32 nParam1 = 2;
  inline bool has_nparam1() const;
  inline void clear_nparam1();
  static const int kNParam1FieldNumber = 2;
  inline ::google::protobuf::int32 nparam1() const;
  inline void set_nparam1(::google::protobuf::int32 value);

  // optional string strParam1 = 3;
  inline bool has_strparam1() const;
  inline void clear_strparam1();
  static const int kStrParam1FieldNumber = 3;
  inline const ::std::string& strparam1() const;
  inline void set_strparam1(const ::std::string& value);
  inline void set_strparam1(const char* value);
  inline void set_strparam1(const char* value, size_t size);
  inline ::std::string* mutable_strparam1();
  inline ::std::string* release_strparam1();
  inline void set_allocated_strparam1(::std::string* strparam1);

  // @@protoc_insertion_point(class_scope:SGFMsg.AckEventResult)
 private:
  inline void set_has_evt_code();
  inline void clear_has_evt_code();
  inline void set_has_nparam1();
  inline void clear_has_nparam1();
  inline void set_has_strparam1();
  inline void clear_has_strparam1();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 evt_code_;
  ::google::protobuf::int32 nparam1_;
  ::std::string* strparam1_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_CommGameMsg_2eproto();
  friend void protobuf_AssignDesc_CommGameMsg_2eproto();
  friend void protobuf_ShutdownFile_CommGameMsg_2eproto();

  void InitAsDefaultInstance();
  static AckEventResult* default_instance_;
};
// -------------------------------------------------------------------

class AccountLoginReq : public ::google::protobuf::Message {
 public:
  AccountLoginReq();
  virtual ~AccountLoginReq();

  AccountLoginReq(const AccountLoginReq& from);

  inline AccountLoginReq& operator=(const AccountLoginReq& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const AccountLoginReq& default_instance();

  void Swap(AccountLoginReq* other);

  // implements Message ----------------------------------------------

  AccountLoginReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AccountLoginReq& from);
  void MergeFrom(const AccountLoginReq& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 clientVersion = 3;
  inline bool has_clientversion() const;
  inline void clear_clientversion();
  static const int kClientVersionFieldNumber = 3;
  inline ::google::protobuf::int32 clientversion() const;
  inline void set_clientversion(::google::protobuf::int32 value);

  // optional bytes security_code = 4;
  inline bool has_security_code() const;
  inline void clear_security_code();
  static const int kSecurityCodeFieldNumber = 4;
  inline const ::std::string& security_code() const;
  inline void set_security_code(const ::std::string& value);
  inline void set_security_code(const char* value);
  inline void set_security_code(const void* value, size_t size);
  inline ::std::string* mutable_security_code();
  inline ::std::string* release_security_code();
  inline void set_allocated_security_code(::std::string* security_code);

  // optional int32 loginMode = 5;
  inline bool has_loginmode() const;
  inline void clear_loginmode();
  static const int kLoginModeFieldNumber = 5;
  inline ::google::protobuf::int32 loginmode() const;
  inline void set_loginmode(::google::protobuf::int32 value);

  // optional bytes device_info = 8;
  inline bool has_device_info() const;
  inline void clear_device_info();
  static const int kDeviceInfoFieldNumber = 8;
  inline const ::std::string& device_info() const;
  inline void set_device_info(const ::std::string& value);
  inline void set_device_info(const char* value);
  inline void set_device_info(const void* value, size_t size);
  inline ::std::string* mutable_device_info();
  inline ::std::string* release_device_info();
  inline void set_allocated_device_info(::std::string* device_info);

  // optional bytes extra_info = 9;
  inline bool has_extra_info() const;
  inline void clear_extra_info();
  static const int kExtraInfoFieldNumber = 9;
  inline const ::std::string& extra_info() const;
  inline void set_extra_info(const ::std::string& value);
  inline void set_extra_info(const char* value);
  inline void set_extra_info(const void* value, size_t size);
  inline ::std::string* mutable_extra_info();
  inline ::std::string* release_extra_info();
  inline void set_allocated_extra_info(::std::string* extra_info);

  // optional bytes access_token = 10;
  inline bool has_access_token() const;
  inline void clear_access_token();
  static const int kAccessTokenFieldNumber = 10;
  inline const ::std::string& access_token() const;
  inline void set_access_token(const ::std::string& value);
  inline void set_access_token(const char* value);
  inline void set_access_token(const void* value, size_t size);
  inline ::std::string* mutable_access_token();
  inline ::std::string* release_access_token();
  inline void set_allocated_access_token(::std::string* access_token);

  // @@protoc_insertion_point(class_scope:SGFMsg.AccountLoginReq)
 private:
  inline void set_has_clientversion();
  inline void clear_has_clientversion();
  inline void set_has_security_code();
  inline void clear_has_security_code();
  inline void set_has_loginmode();
  inline void clear_has_loginmode();
  inline void set_has_device_info();
  inline void clear_has_device_info();
  inline void set_has_extra_info();
  inline void clear_has_extra_info();
  inline void set_has_access_token();
  inline void clear_has_access_token();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* security_code_;
  ::google::protobuf::int32 clientversion_;
  ::google::protobuf::int32 loginmode_;
  ::std::string* device_info_;
  ::std::string* extra_info_;
  ::std::string* access_token_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];

  friend void  protobuf_AddDesc_CommGameMsg_2eproto();
  friend void protobuf_AssignDesc_CommGameMsg_2eproto();
  friend void protobuf_ShutdownFile_CommGameMsg_2eproto();

  void InitAsDefaultInstance();
  static AccountLoginReq* default_instance_;
};
// -------------------------------------------------------------------

class AccountLoginRes : public ::google::protobuf::Message {
 public:
  AccountLoginRes();
  virtual ~AccountLoginRes();

  AccountLoginRes(const AccountLoginRes& from);

  inline AccountLoginRes& operator=(const AccountLoginRes& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const AccountLoginRes& default_instance();

  void Swap(AccountLoginRes* other);

  // implements Message ----------------------------------------------

  AccountLoginRes* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AccountLoginRes& from);
  void MergeFrom(const AccountLoginRes& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 state = 1;
  inline bool has_state() const;
  inline void clear_state();
  static const int kStateFieldNumber = 1;
  inline ::google::protobuf::int32 state() const;
  inline void set_state(::google::protobuf::int32 value);

  // optional string ip = 2;
  inline bool has_ip() const;
  inline void clear_ip();
  static const int kIpFieldNumber = 2;
  inline const ::std::string& ip() const;
  inline void set_ip(const ::std::string& value);
  inline void set_ip(const char* value);
  inline void set_ip(const char* value, size_t size);
  inline ::std::string* mutable_ip();
  inline ::std::string* release_ip();
  inline void set_allocated_ip(::std::string* ip);

  // optional int32 port = 3;
  inline bool has_port() const;
  inline void clear_port();
  static const int kPortFieldNumber = 3;
  inline ::google::protobuf::int32 port() const;
  inline void set_port(::google::protobuf::int32 value);

  // optional bytes game_token = 4;
  inline bool has_game_token() const;
  inline void clear_game_token();
  static const int kGameTokenFieldNumber = 4;
  inline const ::std::string& game_token() const;
  inline void set_game_token(const ::std::string& value);
  inline void set_game_token(const char* value);
  inline void set_game_token(const void* value, size_t size);
  inline ::std::string* mutable_game_token();
  inline ::std::string* release_game_token();
  inline void set_allocated_game_token(::std::string* game_token);

  // @@protoc_insertion_point(class_scope:SGFMsg.AccountLoginRes)
 private:
  inline void set_has_state();
  inline void clear_has_state();
  inline void set_has_ip();
  inline void clear_has_ip();
  inline void set_has_port();
  inline void clear_has_port();
  inline void set_has_game_token();
  inline void clear_has_game_token();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* ip_;
  ::google::protobuf::int32 state_;
  ::google::protobuf::int32 port_;
  ::std::string* game_token_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_CommGameMsg_2eproto();
  friend void protobuf_AssignDesc_CommGameMsg_2eproto();
  friend void protobuf_ShutdownFile_CommGameMsg_2eproto();

  void InitAsDefaultInstance();
  static AccountLoginRes* default_instance_;
};
// -------------------------------------------------------------------

class EnterPlazaReq : public ::google::protobuf::Message {
 public:
  EnterPlazaReq();
  virtual ~EnterPlazaReq();

  EnterPlazaReq(const EnterPlazaReq& from);

  inline EnterPlazaReq& operator=(const EnterPlazaReq& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const EnterPlazaReq& default_instance();

  void Swap(EnterPlazaReq* other);

  // implements Message ----------------------------------------------

  EnterPlazaReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const EnterPlazaReq& from);
  void MergeFrom(const EnterPlazaReq& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required bytes game_token = 1;
  inline bool has_game_token() const;
  inline void clear_game_token();
  static const int kGameTokenFieldNumber = 1;
  inline const ::std::string& game_token() const;
  inline void set_game_token(const ::std::string& value);
  inline void set_game_token(const char* value);
  inline void set_game_token(const void* value, size_t size);
  inline ::std::string* mutable_game_token();
  inline ::std::string* release_game_token();
  inline void set_allocated_game_token(::std::string* game_token);

  // @@protoc_insertion_point(class_scope:SGFMsg.EnterPlazaReq)
 private:
  inline void set_has_game_token();
  inline void clear_has_game_token();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* game_token_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_CommGameMsg_2eproto();
  friend void protobuf_AssignDesc_CommGameMsg_2eproto();
  friend void protobuf_ShutdownFile_CommGameMsg_2eproto();

  void InitAsDefaultInstance();
  static EnterPlazaReq* default_instance_;
};
// ===================================================================


// ===================================================================

// AckEventResult

// required int32 evt_code = 1;
inline bool AckEventResult::has_evt_code() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AckEventResult::set_has_evt_code() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AckEventResult::clear_has_evt_code() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AckEventResult::clear_evt_code() {
  evt_code_ = 0;
  clear_has_evt_code();
}
inline ::google::protobuf::int32 AckEventResult::evt_code() const {
  return evt_code_;
}
inline void AckEventResult::set_evt_code(::google::protobuf::int32 value) {
  set_has_evt_code();
  evt_code_ = value;
}

// optional int32 nParam1 = 2;
inline bool AckEventResult::has_nparam1() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AckEventResult::set_has_nparam1() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AckEventResult::clear_has_nparam1() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AckEventResult::clear_nparam1() {
  nparam1_ = 0;
  clear_has_nparam1();
}
inline ::google::protobuf::int32 AckEventResult::nparam1() const {
  return nparam1_;
}
inline void AckEventResult::set_nparam1(::google::protobuf::int32 value) {
  set_has_nparam1();
  nparam1_ = value;
}

// optional string strParam1 = 3;
inline bool AckEventResult::has_strparam1() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AckEventResult::set_has_strparam1() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AckEventResult::clear_has_strparam1() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AckEventResult::clear_strparam1() {
  if (strparam1_ != &::google::protobuf::internal::kEmptyString) {
    strparam1_->clear();
  }
  clear_has_strparam1();
}
inline const ::std::string& AckEventResult::strparam1() const {
  return *strparam1_;
}
inline void AckEventResult::set_strparam1(const ::std::string& value) {
  set_has_strparam1();
  if (strparam1_ == &::google::protobuf::internal::kEmptyString) {
    strparam1_ = new ::std::string;
  }
  strparam1_->assign(value);
}
inline void AckEventResult::set_strparam1(const char* value) {
  set_has_strparam1();
  if (strparam1_ == &::google::protobuf::internal::kEmptyString) {
    strparam1_ = new ::std::string;
  }
  strparam1_->assign(value);
}
inline void AckEventResult::set_strparam1(const char* value, size_t size) {
  set_has_strparam1();
  if (strparam1_ == &::google::protobuf::internal::kEmptyString) {
    strparam1_ = new ::std::string;
  }
  strparam1_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AckEventResult::mutable_strparam1() {
  set_has_strparam1();
  if (strparam1_ == &::google::protobuf::internal::kEmptyString) {
    strparam1_ = new ::std::string;
  }
  return strparam1_;
}
inline ::std::string* AckEventResult::release_strparam1() {
  clear_has_strparam1();
  if (strparam1_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = strparam1_;
    strparam1_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void AckEventResult::set_allocated_strparam1(::std::string* strparam1) {
  if (strparam1_ != &::google::protobuf::internal::kEmptyString) {
    delete strparam1_;
  }
  if (strparam1) {
    set_has_strparam1();
    strparam1_ = strparam1;
  } else {
    clear_has_strparam1();
    strparam1_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// AccountLoginReq

// optional int32 clientVersion = 3;
inline bool AccountLoginReq::has_clientversion() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AccountLoginReq::set_has_clientversion() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AccountLoginReq::clear_has_clientversion() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AccountLoginReq::clear_clientversion() {
  clientversion_ = 0;
  clear_has_clientversion();
}
inline ::google::protobuf::int32 AccountLoginReq::clientversion() const {
  return clientversion_;
}
inline void AccountLoginReq::set_clientversion(::google::protobuf::int32 value) {
  set_has_clientversion();
  clientversion_ = value;
}

// optional bytes security_code = 4;
inline bool AccountLoginReq::has_security_code() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AccountLoginReq::set_has_security_code() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AccountLoginReq::clear_has_security_code() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AccountLoginReq::clear_security_code() {
  if (security_code_ != &::google::protobuf::internal::kEmptyString) {
    security_code_->clear();
  }
  clear_has_security_code();
}
inline const ::std::string& AccountLoginReq::security_code() const {
  return *security_code_;
}
inline void AccountLoginReq::set_security_code(const ::std::string& value) {
  set_has_security_code();
  if (security_code_ == &::google::protobuf::internal::kEmptyString) {
    security_code_ = new ::std::string;
  }
  security_code_->assign(value);
}
inline void AccountLoginReq::set_security_code(const char* value) {
  set_has_security_code();
  if (security_code_ == &::google::protobuf::internal::kEmptyString) {
    security_code_ = new ::std::string;
  }
  security_code_->assign(value);
}
inline void AccountLoginReq::set_security_code(const void* value, size_t size) {
  set_has_security_code();
  if (security_code_ == &::google::protobuf::internal::kEmptyString) {
    security_code_ = new ::std::string;
  }
  security_code_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AccountLoginReq::mutable_security_code() {
  set_has_security_code();
  if (security_code_ == &::google::protobuf::internal::kEmptyString) {
    security_code_ = new ::std::string;
  }
  return security_code_;
}
inline ::std::string* AccountLoginReq::release_security_code() {
  clear_has_security_code();
  if (security_code_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = security_code_;
    security_code_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void AccountLoginReq::set_allocated_security_code(::std::string* security_code) {
  if (security_code_ != &::google::protobuf::internal::kEmptyString) {
    delete security_code_;
  }
  if (security_code) {
    set_has_security_code();
    security_code_ = security_code;
  } else {
    clear_has_security_code();
    security_code_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional int32 loginMode = 5;
inline bool AccountLoginReq::has_loginmode() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AccountLoginReq::set_has_loginmode() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AccountLoginReq::clear_has_loginmode() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AccountLoginReq::clear_loginmode() {
  loginmode_ = 0;
  clear_has_loginmode();
}
inline ::google::protobuf::int32 AccountLoginReq::loginmode() const {
  return loginmode_;
}
inline void AccountLoginReq::set_loginmode(::google::protobuf::int32 value) {
  set_has_loginmode();
  loginmode_ = value;
}

// optional bytes device_info = 8;
inline bool AccountLoginReq::has_device_info() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void AccountLoginReq::set_has_device_info() {
  _has_bits_[0] |= 0x00000008u;
}
inline void AccountLoginReq::clear_has_device_info() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void AccountLoginReq::clear_device_info() {
  if (device_info_ != &::google::protobuf::internal::kEmptyString) {
    device_info_->clear();
  }
  clear_has_device_info();
}
inline const ::std::string& AccountLoginReq::device_info() const {
  return *device_info_;
}
inline void AccountLoginReq::set_device_info(const ::std::string& value) {
  set_has_device_info();
  if (device_info_ == &::google::protobuf::internal::kEmptyString) {
    device_info_ = new ::std::string;
  }
  device_info_->assign(value);
}
inline void AccountLoginReq::set_device_info(const char* value) {
  set_has_device_info();
  if (device_info_ == &::google::protobuf::internal::kEmptyString) {
    device_info_ = new ::std::string;
  }
  device_info_->assign(value);
}
inline void AccountLoginReq::set_device_info(const void* value, size_t size) {
  set_has_device_info();
  if (device_info_ == &::google::protobuf::internal::kEmptyString) {
    device_info_ = new ::std::string;
  }
  device_info_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AccountLoginReq::mutable_device_info() {
  set_has_device_info();
  if (device_info_ == &::google::protobuf::internal::kEmptyString) {
    device_info_ = new ::std::string;
  }
  return device_info_;
}
inline ::std::string* AccountLoginReq::release_device_info() {
  clear_has_device_info();
  if (device_info_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = device_info_;
    device_info_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void AccountLoginReq::set_allocated_device_info(::std::string* device_info) {
  if (device_info_ != &::google::protobuf::internal::kEmptyString) {
    delete device_info_;
  }
  if (device_info) {
    set_has_device_info();
    device_info_ = device_info;
  } else {
    clear_has_device_info();
    device_info_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional bytes extra_info = 9;
inline bool AccountLoginReq::has_extra_info() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void AccountLoginReq::set_has_extra_info() {
  _has_bits_[0] |= 0x00000010u;
}
inline void AccountLoginReq::clear_has_extra_info() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void AccountLoginReq::clear_extra_info() {
  if (extra_info_ != &::google::protobuf::internal::kEmptyString) {
    extra_info_->clear();
  }
  clear_has_extra_info();
}
inline const ::std::string& AccountLoginReq::extra_info() const {
  return *extra_info_;
}
inline void AccountLoginReq::set_extra_info(const ::std::string& value) {
  set_has_extra_info();
  if (extra_info_ == &::google::protobuf::internal::kEmptyString) {
    extra_info_ = new ::std::string;
  }
  extra_info_->assign(value);
}
inline void AccountLoginReq::set_extra_info(const char* value) {
  set_has_extra_info();
  if (extra_info_ == &::google::protobuf::internal::kEmptyString) {
    extra_info_ = new ::std::string;
  }
  extra_info_->assign(value);
}
inline void AccountLoginReq::set_extra_info(const void* value, size_t size) {
  set_has_extra_info();
  if (extra_info_ == &::google::protobuf::internal::kEmptyString) {
    extra_info_ = new ::std::string;
  }
  extra_info_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AccountLoginReq::mutable_extra_info() {
  set_has_extra_info();
  if (extra_info_ == &::google::protobuf::internal::kEmptyString) {
    extra_info_ = new ::std::string;
  }
  return extra_info_;
}
inline ::std::string* AccountLoginReq::release_extra_info() {
  clear_has_extra_info();
  if (extra_info_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = extra_info_;
    extra_info_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void AccountLoginReq::set_allocated_extra_info(::std::string* extra_info) {
  if (extra_info_ != &::google::protobuf::internal::kEmptyString) {
    delete extra_info_;
  }
  if (extra_info) {
    set_has_extra_info();
    extra_info_ = extra_info;
  } else {
    clear_has_extra_info();
    extra_info_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional bytes access_token = 10;
inline bool AccountLoginReq::has_access_token() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void AccountLoginReq::set_has_access_token() {
  _has_bits_[0] |= 0x00000020u;
}
inline void AccountLoginReq::clear_has_access_token() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void AccountLoginReq::clear_access_token() {
  if (access_token_ != &::google::protobuf::internal::kEmptyString) {
    access_token_->clear();
  }
  clear_has_access_token();
}
inline const ::std::string& AccountLoginReq::access_token() const {
  return *access_token_;
}
inline void AccountLoginReq::set_access_token(const ::std::string& value) {
  set_has_access_token();
  if (access_token_ == &::google::protobuf::internal::kEmptyString) {
    access_token_ = new ::std::string;
  }
  access_token_->assign(value);
}
inline void AccountLoginReq::set_access_token(const char* value) {
  set_has_access_token();
  if (access_token_ == &::google::protobuf::internal::kEmptyString) {
    access_token_ = new ::std::string;
  }
  access_token_->assign(value);
}
inline void AccountLoginReq::set_access_token(const void* value, size_t size) {
  set_has_access_token();
  if (access_token_ == &::google::protobuf::internal::kEmptyString) {
    access_token_ = new ::std::string;
  }
  access_token_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AccountLoginReq::mutable_access_token() {
  set_has_access_token();
  if (access_token_ == &::google::protobuf::internal::kEmptyString) {
    access_token_ = new ::std::string;
  }
  return access_token_;
}
inline ::std::string* AccountLoginReq::release_access_token() {
  clear_has_access_token();
  if (access_token_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = access_token_;
    access_token_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void AccountLoginReq::set_allocated_access_token(::std::string* access_token) {
  if (access_token_ != &::google::protobuf::internal::kEmptyString) {
    delete access_token_;
  }
  if (access_token) {
    set_has_access_token();
    access_token_ = access_token;
  } else {
    clear_has_access_token();
    access_token_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// AccountLoginRes

// required int32 state = 1;
inline bool AccountLoginRes::has_state() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AccountLoginRes::set_has_state() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AccountLoginRes::clear_has_state() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AccountLoginRes::clear_state() {
  state_ = 0;
  clear_has_state();
}
inline ::google::protobuf::int32 AccountLoginRes::state() const {
  return state_;
}
inline void AccountLoginRes::set_state(::google::protobuf::int32 value) {
  set_has_state();
  state_ = value;
}

// optional string ip = 2;
inline bool AccountLoginRes::has_ip() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AccountLoginRes::set_has_ip() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AccountLoginRes::clear_has_ip() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AccountLoginRes::clear_ip() {
  if (ip_ != &::google::protobuf::internal::kEmptyString) {
    ip_->clear();
  }
  clear_has_ip();
}
inline const ::std::string& AccountLoginRes::ip() const {
  return *ip_;
}
inline void AccountLoginRes::set_ip(const ::std::string& value) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
}
inline void AccountLoginRes::set_ip(const char* value) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
}
inline void AccountLoginRes::set_ip(const char* value, size_t size) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    ip_ = new ::std::string;
  }
  ip_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AccountLoginRes::mutable_ip() {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    ip_ = new ::std::string;
  }
  return ip_;
}
inline ::std::string* AccountLoginRes::release_ip() {
  clear_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = ip_;
    ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void AccountLoginRes::set_allocated_ip(::std::string* ip) {
  if (ip_ != &::google::protobuf::internal::kEmptyString) {
    delete ip_;
  }
  if (ip) {
    set_has_ip();
    ip_ = ip;
  } else {
    clear_has_ip();
    ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional int32 port = 3;
inline bool AccountLoginRes::has_port() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AccountLoginRes::set_has_port() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AccountLoginRes::clear_has_port() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AccountLoginRes::clear_port() {
  port_ = 0;
  clear_has_port();
}
inline ::google::protobuf::int32 AccountLoginRes::port() const {
  return port_;
}
inline void AccountLoginRes::set_port(::google::protobuf::int32 value) {
  set_has_port();
  port_ = value;
}

// optional bytes game_token = 4;
inline bool AccountLoginRes::has_game_token() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void AccountLoginRes::set_has_game_token() {
  _has_bits_[0] |= 0x00000008u;
}
inline void AccountLoginRes::clear_has_game_token() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void AccountLoginRes::clear_game_token() {
  if (game_token_ != &::google::protobuf::internal::kEmptyString) {
    game_token_->clear();
  }
  clear_has_game_token();
}
inline const ::std::string& AccountLoginRes::game_token() const {
  return *game_token_;
}
inline void AccountLoginRes::set_game_token(const ::std::string& value) {
  set_has_game_token();
  if (game_token_ == &::google::protobuf::internal::kEmptyString) {
    game_token_ = new ::std::string;
  }
  game_token_->assign(value);
}
inline void AccountLoginRes::set_game_token(const char* value) {
  set_has_game_token();
  if (game_token_ == &::google::protobuf::internal::kEmptyString) {
    game_token_ = new ::std::string;
  }
  game_token_->assign(value);
}
inline void AccountLoginRes::set_game_token(const void* value, size_t size) {
  set_has_game_token();
  if (game_token_ == &::google::protobuf::internal::kEmptyString) {
    game_token_ = new ::std::string;
  }
  game_token_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AccountLoginRes::mutable_game_token() {
  set_has_game_token();
  if (game_token_ == &::google::protobuf::internal::kEmptyString) {
    game_token_ = new ::std::string;
  }
  return game_token_;
}
inline ::std::string* AccountLoginRes::release_game_token() {
  clear_has_game_token();
  if (game_token_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = game_token_;
    game_token_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void AccountLoginRes::set_allocated_game_token(::std::string* game_token) {
  if (game_token_ != &::google::protobuf::internal::kEmptyString) {
    delete game_token_;
  }
  if (game_token) {
    set_has_game_token();
    game_token_ = game_token;
  } else {
    clear_has_game_token();
    game_token_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// EnterPlazaReq

// required bytes game_token = 1;
inline bool EnterPlazaReq::has_game_token() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void EnterPlazaReq::set_has_game_token() {
  _has_bits_[0] |= 0x00000001u;
}
inline void EnterPlazaReq::clear_has_game_token() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void EnterPlazaReq::clear_game_token() {
  if (game_token_ != &::google::protobuf::internal::kEmptyString) {
    game_token_->clear();
  }
  clear_has_game_token();
}
inline const ::std::string& EnterPlazaReq::game_token() const {
  return *game_token_;
}
inline void EnterPlazaReq::set_game_token(const ::std::string& value) {
  set_has_game_token();
  if (game_token_ == &::google::protobuf::internal::kEmptyString) {
    game_token_ = new ::std::string;
  }
  game_token_->assign(value);
}
inline void EnterPlazaReq::set_game_token(const char* value) {
  set_has_game_token();
  if (game_token_ == &::google::protobuf::internal::kEmptyString) {
    game_token_ = new ::std::string;
  }
  game_token_->assign(value);
}
inline void EnterPlazaReq::set_game_token(const void* value, size_t size) {
  set_has_game_token();
  if (game_token_ == &::google::protobuf::internal::kEmptyString) {
    game_token_ = new ::std::string;
  }
  game_token_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* EnterPlazaReq::mutable_game_token() {
  set_has_game_token();
  if (game_token_ == &::google::protobuf::internal::kEmptyString) {
    game_token_ = new ::std::string;
  }
  return game_token_;
}
inline ::std::string* EnterPlazaReq::release_game_token() {
  clear_has_game_token();
  if (game_token_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = game_token_;
    game_token_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void EnterPlazaReq::set_allocated_game_token(::std::string* game_token) {
  if (game_token_ != &::google::protobuf::internal::kEmptyString) {
    delete game_token_;
  }
  if (game_token) {
    set_has_game_token();
    game_token_ = game_token;
  } else {
    clear_has_game_token();
    game_token_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace SGFMsg

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_CommGameMsg_2eproto__INCLUDED
