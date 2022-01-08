#ifndef _INC_XPLATFORM_SSL_CTX_H
#define _INC_XPLATFORM_SSL_CTX_H

#include <XPlatform.core/XP_IObject.h>

#include<string>

namespace XPlatform {
	namespace Net {
		namespace SSL {
			enum class SSLFileType {
				ASN1 = 1,
				PEM = ASN1 << 1
			};

			typedef int (*pfn_XPlatformPasswordCallBack)(char* buf, int size, int rwflag, void* userdata);

			class Ctx : public XPlatform::core::XPlatformCrossModuleObject{
			public:

				virtual bool SetCertificateFile(const std::string& Path, const XPlatform::Net::SSL::SSLFileType& FileType) = 0;
				virtual bool SetPrivateKeyFile(const std::string& Path, const XPlatform::Net::SSL::SSLFileType& FileType) = 0;

				virtual bool LoadVerifyLocations(const std::string& CAFile, const std::string& CAPath) = 0;

				virtual void SetPasswordCallback(pfn_XPlatformPasswordCallBack pfn_Callback) = 0;
				virtual void SetDefualtPasswordCallbackUserData(void* p_Data) = 0;

				virtual void Release() = 0;

			};
		}
	}
}

#endif