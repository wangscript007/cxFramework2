#ifndef HTTP1CLIENT_H
#define HTTP1CLIENT_H

#include "httpv1_base.h"
#include "http_cookies_clientside.h"
#include "http_cookies_serverside.h"
#include "security/http_security_xframeopts.h"
#include "security/http_security_xssprotection.h"
#include "security/http_security_hsts.h"

// TODO: https://en.wikipedia.org/wiki/Media_type
// TODO: cuando el request para doh5 este listo, pre-procesar primero el request y luego recibir los datos.
// TODO: post data? <<< IMPORTANT.
// TODO: reuse the connection?...
// TODO: header: :scheme:https (begins with :)

namespace CX2 { namespace Network { namespace HTTP {

class HTTPv1_Client : public HTTPv1_Base
{
public:
    HTTPv1_Client(Memory::Streams::Streamable * sobject);
    /**
     * @brief setClientRequest Set client request
     * @param hostName host name
     * @param uriPath requested Uniform Resource Indetifier Path
     */
    void setClientRequest(const std::string & hostName, const std::string & uriPath);
    /**
     * @brief setDontTrackFlag Set Don't track flag
     * @param dnt true: don't track
     */
    void setDontTrackFlag(bool dnt = true);
    /**
     * @brief setReferer Set Referer URL
     * @param refererURL referer URL
     */
    void setReferer(const std::string & refererURL);
    /**
     * @brief addCookieValue Add cookie.
     * @param cookieName Cookie Name
     * @param cookieVal Coookie Value
     */
    void addCookie(const std::string & cookieName, const std::string & cookieVal);
    /**
     * @brief setClientUserAgent Set Client User Agent
     * @param userAgent User Agent String (eg. Wgetty/1.1)
     */
    void setClientUserAgent(const std::string &userAgent);
    /**
     * @brief setAuthorizationBasic
     * @param user
     * @param pass
     */
    void setBasicAuthorization(const std::string &user, const std::string &pass);
    /**
     * @brief getServerCookies Get the server cookies container with the information of received cookies
     * @return server cookies container.
     */
    HTTP_Cookies_ServerSide * getServerCookies();
    /**
     * @brief getServerContentType Get Server Content Type
     * @return Content Type
     */
    std::string getServerContentType() const;
    /**
     * @brief getSecurityNoSniffContentType Get if No-Sniff option was sent
     * @return
     */
    bool getSecurityNoSniffContentType() const;
    /**
     * @brief getSecXFrameOpts Get Security XFrame Options
     * @return
     */
    HTTP_Security_XFrameOpts getSecXFrameOpts() const;
    /**
     * @brief getSecXSSProtection Get XSS Protection Header from server
     * @return
     */
    HTTP_Security_XSSProtection getSecXSSProtection() const;
    /**
     * @brief getSecHSTS Get HSTS Policy...
     * @return
     */
    HTTP_Security_HSTS getSecHSTS() const;

protected:
    bool initProtocol() override;

    void * getThis() override { return this; }
    bool changeToNextParser() override;

    /**
      // TODO:
     * @brief onStart emit this signal when download starts
     */
    virtual void onStart() {}
    /**
     * // TODO:
     * @brief onProgress emit progress percentage when data is received.
     * @param progressPct percentage using scale /10000
     */
    virtual void onProgress(const uint16_t &progressPct, const uint64_t &progressBytes, const uint64_t &progressExpectedBytes) {}
    /**
      // TODO:
     * @brief onFinished emit this signal when connection is ended.
     */
    virtual void onFinished() {}
private:
    void parseHeaders2ServerCookies();
    Memory::Streams::Parsing::SubParser *parseHeaders2TransmitionMode();

    bool streamClientHeaders(Memory::Streams::Status &wrStat);

    HTTP_Cookies_ClientSide clientCookies;
    HTTP_Cookies_ServerSide serverCookies;
    HTTP_Security_XFrameOpts secXFrameOpts;
    HTTP_Security_HSTS secHSTS;
    HTTP_Security_XSSProtection secXSSProtection;

    std::string serverContentType;
    bool securityNoSniffContentType;
};

}}}

#endif // HTTP1CLIENT_H
