<h1 align="center"> TCP Socket creation </h1>

## [go back](../examples.md)

---
## For IPv4:
``` c++
    XPlatform::Net::XP_ISocket* m_pxiSocket = 
    reinterpret_cast<XPlatform::Net::XP_ISocket*>(
        XPlatform::core::Engine::GetInstance()->CreateExtensionClass(NetExtInfo->ExtId, XPLATFORM_EXT_NET_CLASS_ID_TCP_SOCKET)
    );
```

## For IPv6:

``` c++
    XPlatform::Net::XP_ISocket* m_pxiSocket = 
    reinterpret_cast<XPlatform::Net::XP_ISocket*>(
        XPlatform::core::Engine::GetInstance()->CreateExtensionClass(NetExtInfo->ExtId, XPLATFORM_EXT_NET_CLASS_ID_TCP_SOCKETv6)
    );
```

--- 
## [go back](../examples.md)