<h1 align="center"> UDP Socket creation </h1>

## [go back](../examples.md)

---
## For IPv4:
``` c++
    XPlatform::Net::XP_IUdpSocket* m_pxiSocket = 
    reinterpret_cast<XPlatform::Net::XP_IUdpSocket*>(
        XPlatform::core::Engine::GetInstance()->CreateExtensionClass(NetExtInfo->ExtId, XPLATFORM_EXT_NET_CLASS_ID_UDP_SOCKET)
    );
```

## For IPv6:

``` c++
    XPlatform::Net::XP_IUdpSocket* m_pxiSocket = 
    reinterpret_cast<XPlatform::Net::XP_IUdpSocket*>(
        XPlatform::core::Engine::GetInstance()->CreateExtensionClass(NetExtInfo->ExtId, XPLATFORM_EXT_NET_CLASS_ID_UDP_SOCKETv6)
    );
```

--- 
## [go back](../examples.md)