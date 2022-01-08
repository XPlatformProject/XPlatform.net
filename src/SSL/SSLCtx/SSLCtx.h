#ifndef _SRC_XPLATFORM_NET_SSL_CTX_H
#define _SRC_XPLATFORM_NET_SSL_CTX_H

#include<XPlatform.net/SSL/SSLCtx.h>

#include<openssl/ssl.h>

namespace XPlatform {
	namespace Net {
		namespace SSL {
			class Context : public XPlatform::Net::SSL::Ctx {

				SSL_CTX* m_pCtx;

			public:

				Context(SSL_CTX* _Ctx);

				bool SetCertificateFile(const std::string& Path, const XPlatform::Net::SSL::SSLFileType& FileType) override;
				bool SetPrivateKeyFile(const std::string& Path, const XPlatform::Net::SSL::SSLFileType& FileType) override;

				bool LoadVerifyLocations(const std::string& CAFile, const std::string& CAPath) override;

				void SetPasswordCallback(pfn_XPlatformPasswordCallBack pfn_Callback) override;
				void SetDefualtPasswordCallbackUserData(void* p_Data) override;

				SSL_CTX* GetRawHandle();

				~Context();

				void Release() override;
			};
		}
	}
}

#endif