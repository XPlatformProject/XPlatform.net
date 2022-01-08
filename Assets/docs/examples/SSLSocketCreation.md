<h1 align="center"> SSL TCP Socket creation </h1>

## [go back](../examples.md)

---
## For IPv4:
``` c++

    XPlatform::Net::SSL::pfn_XPlatformCreateContextFunction XPlatformCreateContextFunction =
	reinterpret_cast<XPlatform::Net::SSL::pfn_XPlatformCreateContextFunction>(
		m_pEngine->GetExtensionModule(NetExtInfo->ExtId)->GetProc(XPlatform::Net::SSL::m_pXPlatformCreateContextFunctionName)
	);

    XPlatform::Net::SSL::Ctx* m_pCtx = XPlatformCreateContextFunction(false);

    // for server
	if (!m_pCtx->SetCertificateFile("certificate file path", XPlatform::Net::SSL::SSLFileType::PEM)) {
		m_pCtx->Release();
		return false;
	}

    // for server
    // Set PrivateKey password
    m_pCtx->SetDefualtPasswordCallbackUserData("pass");

    // for server
    if (!m_pCtx->SetPrivateKeyFile("private key file path", XPlatform::Net::SSL::SSLFileType::PEM)) {
		std::cout << "{SetPrivateKeyFile}: Wrong password or file dont found '" << m_sPrivateKeyFilePath << std::endl;
		m_pCtx->Release();
		return false;
	}

	XPlatformCreateSSLTCPSocketFunction =
		reinterpret_cast<XPlatform::Net::SSL::pfn_XPlatformCreateSSLTCPSocketFunction>(
			m_pEngine->GetExtensionModule(NetExtInfo->ExtId)->GetProc(XPlatform::Net::SSL::m_pXPlatformCreateSSLTCPSocketFunctionName)
	);

    XPlatform::Net::XP_ISocket* m_pxiSocket;

    m_pxiSocket = XPlatformCreateSSLTCPSocketFunction(m_pCtx);
```

## For IPv6:

``` c++

    XPlatform::Net::SSL::pfn_XPlatformCreateContextFunction XPlatformCreateContextFunction =
	reinterpret_cast<XPlatform::Net::SSL::pfn_XPlatformCreateContextFunction>(
		m_pEngine->GetExtensionModule(NetExtInfo->ExtId)->GetProc(XPlatform::Net::SSL::m_pXPlatformCreateContextFunctionName)
	);

    XPlatform::Net::SSL::Ctx* m_pCtx = XPlatformCreateContextFunction(false);

    // for server
	if (!m_pCtx->SetCertificateFile("certificate file path", XPlatform::Net::SSL::SSLFileType::PEM)) {
		m_pCtx->Release();
		return false;
	}

    // for server
    // Set PrivateKey password
    m_pCtx->SetDefualtPasswordCallbackUserData("pass");

    // for server
    if (!m_pCtx->SetPrivateKeyFile("private key file path", XPlatform::Net::SSL::SSLFileType::PEM)) {
		std::cout << "{SetPrivateKeyFile}: Wrong password or file dont found '" << m_sPrivateKeyFilePath << std::endl;
		m_pCtx->Release();
		return false;
	}

	XPlatformCreateSSLTCPSocketFunction =
		reinterpret_cast<XPlatform::Net::SSL::pfn_XPlatformCreateSSLTCPSocketFunction>(
			m_pEngine->GetExtensionModule(NetExtInfo->ExtId)->GetProc(XPlatform::Net::SSL::m_pXPlatformCreateSSLTCPSocketV6FunctionName)
	);

    XPlatform::Net::XP_ISocket* m_pxiSocket;

    m_pxiSocket = XPlatformCreateSSLTCPSocketFunction(m_pCtx);
```

--- 
## [go back](../examples.md)