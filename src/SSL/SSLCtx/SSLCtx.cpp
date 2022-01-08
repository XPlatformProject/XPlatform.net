#include "SSLCtx.h"

#include "../../net.h"

#include<XFmt/XFmt.h>

int SSLFileTypeToInt(const XPlatform::Net::SSL::SSLFileType& FileType) {
	switch (FileType){
	case XPlatform::Net::SSL::SSLFileType::ASN1:
		return SSL_FILETYPE_ASN1;
	case  XPlatform::Net::SSL::SSLFileType::PEM:
		return SSL_FILETYPE_PEM;
	}

	return NULL;
}

XPlatform::Net::SSL::Context::Context(SSL_CTX* _Ctx) : m_pCtx(_Ctx) {
}

bool XPlatform::Net::SSL::Context::SetCertificateFile(const std::string& Path, const XPlatform::Net::SSL::SSLFileType& FileType){
	int res = SSL_CTX_use_certificate_file(m_pCtx, Path.c_str(), SSLFileTypeToInt(FileType));

	if (res <= 0) {
		XPlatform::core::Engine::GetInstance()->GetMsgCallback()(
		XFmt::Fmt("[XPlatfrom][net]:openssl failed to use certificate '%s', openssl function 'SSL_CTX_use_certificate_file' result: %i", Path.c_str(), res).c_str(),
		XPlatform::Api::XPResult::XPLATFORM_RESULT_FAILED,
		_NetExtInf.ExtId
		);

		return false;
	}

	return true;
}

bool XPlatform::Net::SSL::Context::SetPrivateKeyFile(const std::string& Path, const XPlatform::Net::SSL::SSLFileType& FileType){
	int res = SSL_CTX_use_PrivateKey_file(m_pCtx, Path.c_str(), SSLFileTypeToInt(FileType));
	if (res <= 0) {
		XPlatform::core::Engine::GetInstance()->GetMsgCallback()(
			XFmt::Fmt("[XPlatfrom][net]:openssl failed to use private key file '%s', openssl function 'SSL_CTX_use_PrivateKey_file' result: %i", Path.c_str(), res).c_str(),
			XPlatform::Api::XPResult::XPLATFORM_RESULT_FAILED,
			_NetExtInf.ExtId
		);

		return false;
	}

	return true;
}

bool XPlatform::Net::SSL::Context::LoadVerifyLocations(const std::string& CAFile, const std::string& CAPath){
	int res = SSL_CTX_load_verify_locations(m_pCtx, CAFile.c_str(), CAPath.c_str());
	
	if (res <= 0) {
		XPlatform::core::Engine::GetInstance()->GetMsgCallback()(
			XFmt::Fmt("[XPlatfrom][net]:openssl failed to use verify loacation file file '%s', openssl function 'SSL_CTX_load_verify_locations' result: %i", CAFile.c_str(), res).c_str(),
			XPlatform::Api::XPResult::XPLATFORM_RESULT_FAILED,
			_NetExtInf.ExtId
			);

		return false;
	}

	return true;
}

void XPlatform::Net::SSL::Context::SetPasswordCallback(pfn_XPlatformPasswordCallBack pfn_Callback){
	SSL_CTX_set_default_passwd_cb(m_pCtx, reinterpret_cast<pem_password_cb*>(pfn_Callback));
}

void XPlatform::Net::SSL::Context::SetDefualtPasswordCallbackUserData(void* p_Data){
	SSL_CTX_set_default_passwd_cb_userdata(m_pCtx, p_Data);
}

SSL_CTX* XPlatform::Net::SSL::Context::GetRawHandle(){
	return m_pCtx;
}

XPlatform::Net::SSL::Context::~Context(){
	if(m_pCtx != NULL)
	SSL_CTX_free(m_pCtx);
}

void XPlatform::Net::SSL::Context::Release(){
	delete this;
}
