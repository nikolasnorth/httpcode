#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tl/expected.hpp>

namespace httpcode {

/// List of HTTP status codes

using description =
    std::tuple<std::string_view, std::string_view, std::string_view>;

// Map consisting of HTTP status codes and their respective descriptions. Each
// description  contains a short description (e.g. 'OK'), a longer description
// (e.g. 'The request has succeeded.'), and a URL to learn more about the given
// HTTP status code (e.g. `https://httpstatuses.io/200`). Each entry in the map
// has the following format: {code: (short_desc, long_desc, url)}
static const std::map<unsigned int, description> codes = {
    {100,
     {"Continue",
      "The initial part of a request has been received and has not yet "
      "been rejected by the server. The server intends to send a final "
      "response after the request has been fully received and acted "
      "upon.",
      "https://httpstatuses.io/100"}},
    {101,
     {"Switching Protocols",
      "The server understands and is willing to comply with the client's "
      "request, via the Upgrade header field, for a change in the "
      "application protocol being used on this connection.",
      "https://httpstatuses.io/101"}},
    {102,
     {"Processing",
      "An interim response used to inform the client that the server has "
      "accepted the complete request, but has not yet completed it.",
      "https://httpstatuses.io/102"}},
    {103,
     {"Early Hints",
      "This status code indicates to the client that the server is likely "
      "to send a final response with the header fields included in the "
      "informational response.",
      "https://httpstatuses.io/103"}},
    {200,
     {"Continue", "The request has succeeded.", "https://httpstatuses.io/200"}},
    {201,
     {"Created",
      "The request has been fulfilled and has resulted in one or more new "
      "resources being created.",
      "https://httpstatuses.io/201"}},
    {202,
     {"Accepted",
      "The request has been accepted for processing, but the processing "
      "has "
      "not been completed. The request might or might not eventually be "
      "acted upon, as it might be disallowed when processing actually "
      "takes "
      "place.",
      "https://httpstatuses.io/202"}},
    {203,
     {"Non-authoritative information",
      "The request was successful but the enclosed payload has been "
      "modified from that of the origin server's 200 OK response by a "
      "transforming proxy.",
      "https://httpstatuses.io/203"}},
    {204,
     {"No Content",
      "The server has successfully fulfilled the request and that there is "
      "no additional content to send in the response payload body.",
      "https://httpstatuses.io/204"}},
    {205,
     {"Reset Content",
      "The server has fulfilled the request and desires that the user "
      "agent "
      "reset the \"document view\", which caused the request to be sent, "
      "to "
      "its original state as received from the origin server.",
      "https://httpstatuses.io/205"}},
    {206,
     {"Partial Content",
      "The server is successfully fulfilling a range request for the "
      "target "
      "resource by transferring one or more parts of the selected "
      "representation that correspond to the satisfiable ranges found in "
      "the request's Range header field.",
      "https://httpstatuses.io/206"}},
    {207,
     {"Multi-Status",
      "A Multi-Status response conveys information about multiple "
      "resources "
      "in situations where multiple status codes might be appropriate.",
      "https://httpstatuses.io/207"}},
    {208,
     {"Already Reported",
      "Used inside a DAV: propstat response element to avoid enumerating "
      "the internal members of multiple bindings to the same collection "
      "repeatedly.",
      "https://httpstatuses.io/208"}},
    {226,
     {"IM Used",
      "The server has fulfilled a GET request for the resource, and the "
      "response is a representation of the result of one or more "
      "instance-manipulations applied to the current instance.",
      "https://httpstatuses.io/226"}},
    {300,
     {"Multiple Choices",
      "The target resource has more than one representation, each with its "
      "own more specific identifier, and information about the "
      "alternatives is being provided so that the user (or user agent) can "
      "select a preferred representation by redirecting its request to one "
      "or more of those identifiers.",
      "https://httpstatuses.io/300"}},
    {301,
     {"Moved Permanently",
      "The target resource has been assigned a new permanent URI and any "
      "future references to this resource ought to use one of the enclosed "
      "URIs.",
      "https://httpstatuses.io/301"}},
    {302,
     {"Found",
      "The target resource resides temporarily under a different URI. "
      "Since the redirection might be altered on occasion, the client "
      "ought to continue to use the effective request URI for future "
      "requests.",
      "https://httpstatuses.io/302"}},
    {303,
     {"See Other",
      "The server is redirecting the user agent to a different resource, "
      "as indicated by a URI in the Location header field, which is "
      "intended to provide an indirect response to the original request.",
      "https://httpstatuses.io/303"}},
    {304,
     {"Not Modified",
      "A conditional GET or HEAD request has been received and would have "
      "resulted in a 200 OK response if it were not for the fact that the "
      "condition evaluated to false.",
      "https://httpstatuses.io/304"}},
    {305,
     {"Use Proxy",
      "Defined in a previous version of this specification and is now "
      "deprecated, due to security concerns regarding in-band "
      "configuration of a proxy.",
      "https://httpstatuses.io/305"}},
    {307,
     {"Temporary Redirect",
      "The target resource resides temporarily under a different URI and "
      "the user agent MUST NOT change the request method if it performs an "
      "automatic redirection to that URI.",
      "https://httpstatuses.io/307"}},
    {308,
     {"Permanent Redirect",
      "The server has fulfilled a GET request for the resource, and the "
      "response is a representation of the result of one or more "
      "instance-manipulations applied to the current instance.",
      "https://httpstatuses.io/308"}},
    {400,
     {"Bad Request",
      "The server cannot or will not process the request due to something "
      "that is perceived to be a client error (e.g., malformed request "
      "syntax, invalid request message framing, or deceptive request "
      "routing).",
      "https://httpstatuses.io/400"}},
    {401,
     {"Unauthorized",
      "The request has not been applied because it lacks valid "
      "authentication credentials for the target resource.",
      "https://httpstatus.io/401"}},
    {402,
     {"Payment Required", "Reserved for future use.",
      "https://httpstatuses.io/402"}},
    {403,
     {"Forbidden",
      "The server understood the request but refuses to authorize it.",
      "https://httpstatuses.io/403"}},
    {404,
     {"Not Found",
      "The origin server did not find a current representation for the "
      "target resource or is not willing to disclose that one exists.",
      "https://httpstatuses.io/404"}},
    {405,
     {"Method Not Allowed",
      "The method received in the request-line is known by the origin "
      "server but not supported by the target resource.",
      "https://httpstatuses.io/405"}},
    {406,
     {"Not Acceptable",
      "The target resource does not have a current representation that "
      "would be acceptable to the user agent, according to the proactive "
      "negotiation header fields received in the request, and the server "
      "is unwilling to supply a default representation.",
      "https://httpstatuses.io/406"}},
    {407,
     {"Proxy Authentication Required",
      "Similar to 401 Unauthorized, but it indicates that the client needs "
      "to authenticate itself in order to use a proxy.",
      "https://httpstatuses.io/407"}},
    {408,
     {"Request Timeout",
      "The server did not receive a complete request message within the "
      "time that it was prepared to wait.",
      "https://httpstatuses.io/408"}},
    {409,
     {"Conflict",
      "The request could not be completed due to a conflict with the "
      "current state of the target resource. This code is used in "
      "situations where the user might be able to resolve the conflict and "
      "resubmit the request.",
      "https://httpstatuses.io/409"}},
    {410,
     {"Gone",
      "The target resource is no longer available at the origin server and "
      "that this condition is likely to be permanent.",
      "https://httpstatuses.io/410"}},
    {411,
     {"Length Required",
      "The server refuses to accept the request without a defined "
      "Content-Length.",
      "https://httpstatuses.io/411"}},
    {412,
     {"Precondition Failed",
      "One or more conditions given in the request header fields evaluated "
      "to false when tested on the server.",
      "https://httpstatuses.io/412"}},
    {413,
     {"Payload Too Large",
      "The server is refusing to process a request because the request "
      "payload is larger than the server is willing or able to process.",
      "https://httpstatuses.io/413"}},
    {414,
     {"Request-URI Too Long",
      "The server is refusing to service the request because the "
      "request-target is longer than the server is willing to interpret.",
      "https://httpstatuses.io/414"}},
    {415,
     {"Unsupported Media Type",
      "The origin server is refusing to service the request because the "
      "payload is in a format not supported by this method on the target "
      "resource.",
      "https://httpstatuses.io/415"}},
    {416,
     {"Requested Range Not Satisfiable",
      "None of the ranges in the request's Range header field1 overlap the "
      "current extent of the selected resource or that the set of ranges "
      "requested has been rejected due to invalid ranges or an excessive "
      "request of small or overlapping ranges.",
      "https://httpstatuses.io/416"}},
    {417,
     {"Expectation Failed",
      "The expectation given in the request's Expect header field could "
      "not be met by at least one of the inbound servers.",
      "https://httpstatuses.io/417"}},
    {418,
     {"I’m a teapot",
      "Any attempt to brew coffee with a teapot should result in the error "
      "code \"418 I'm a teapot\". The resulting entity body MAY be short "
      "and stout.",
      "https://httpstatuses.io/418"}},
    {421,
     {"Misdirected Request",
      "The request was directed at a server that is not able to produce a "
      "response. This can be sent by a server that is not configured to "
      "produce responses for the combination of scheme and authority that "
      "are included in the request URI.",
      "https://httpstatuses.io/421"}},
    {422,
     {"Unprocessable Entity",
      "The server understands the content type of the request entity "
      "(hence a 415 Unsupported Media Type status code is inappropriate), "
      "and the syntax of the request entity is correct (thus a 400 Bad "
      "Request status code is inappropriate) but was unable to process the "
      "contained instructions.",
      "https://httpstatuses.io/422"}},
    {423,
     {"Locked", "The source or destination resource of a method is locked.",
      "https://httpstatuses.io/423"}},
    {424,
     {"Failed Dependency",
      "The method could not be performed on the resource because the "
      "requested action depended on another action and that action "
      "failed.",
      "https://httpstatuses.io/424"}},
    {426,
     {"Upgrade Required",
      "The server refuses to perform the request using the current "
      "protocol but might be willing to do so after the client upgrades to "
      "a different protocol.",
      "https://httpstatuses.io/426"}},
    {428,
     {"Precondition Required",
      "The origin server requires the request to be conditional.",
      "https://httpstatuses.io/428"}},
    {429,
     {"Too Many Requests",
      "The user has sent too many requests in a given amount of time "
      "(\"rate limiting\").",
      "https://httpstatuses.io/429"}},
    {431,
     {"Request Header Fields Too Large",
      "The server is unwilling to process the request because its header "
      "fields are too large. The request MAY be resubmitted after reducing "
      "the size of the request header fields.",
      "https://httpstatuses.io/431"}},
    {444,
     {"Connection Closed Without Response",
      "A non-standard status code used to instruct nginx to close the "
      "connection without sending a response to the client, most commonly "
      "used to deny malicious or malformed requests.",
      "https://httpstatuses.io/444"}},
    {451,
     {"Unavailable For Legal Reasons",
      "The server is denying access to the resource as a consequence of a "
      "legal demand.",
      "https://httpstatuses.io/451"}},
    {499,
     {"Client Closed Request",
      "A non-standard status code introduced by nginx for the case when a "
      "client closes the connection while nginx is processing the "
      "request.",
      "https://httpstatuses.io/499"}},
    {500,
     {"Internal Server Error",
      "The server encountered an unexpected condition that prevented it "
      "from fulfilling the request.",
      "https://httpstatuses.io/500"}},
    {501,
     {"Not Implemented",
      "The server does not support the functionality required to fulfill "
      "the request.",
      "https://httpstatuses.io/501"}},
    {502,
     {"Bad Gateway",
      "The server, while acting as a gateway or proxy, received an invalid "
      "response from an inbound server it accessed while attempting to "
      "fulfill the request.",
      "https://httpstatuses.io/502"}},
    {503,
     {"Service Unavailable",
      "The server is currently unable to handle the request due to a "
      "temporary overload or scheduled maintenance, which will likely be "
      "alleviated after some delay.",
      "https://httpstatuses.io/503"}},
    {504,
     {"Gateway Timeout",
      "The server, while acting as a gateway or proxy, did not receive a "
      "timely response from an upstream server it needed to access in "
      "order to complete the request.",
      "https://httpstatuses.io/504"}},
    {505,
     {"HTTP Version Not Supported",
      "The server does not support, or refuses to support, the major "
      "version of HTTP that was used in the request message.",
      "https://httpstatuses.io/505"}},
    {506,
     {"Variant Also Negotiates",
      "The server has an internal configuration error: the chosen variant "
      "resource is configured to engage in transparent content negotiation "
      "itself, and is therefore not a proper end point in the negotiation "
      "process.",
      "https://httpstatuses.io/506"}},
    {507,
     {"Insufficient Storage",
      "The method could not be performed on the resource because the "
      "server is unable to store the representation needed to successfully "
      "complete the request.",
      "https://httpstatuses.io/507"}},
    {508,
     {"Loop Detected",
      "The server terminated an operation because it encountered an "
      "infinite loop while processing a request with \"Depth: infinity\". "
      "This status indicates that the entire operation failed.",
      "https://httpstatuses.io/508"}},
    {510,
     {"Not Extended",
      "The policy for accessing the resource has not been met in the "
      "request. The server should send back all the information necessary "
      "for the client to issue an extended request.",
      "https://httpstatuses.io/510"}},
    {511,
     {"Network Authentication Required",
      "The client needs to authenticate to gain network access.",
      "https://httpstatuses.io/511"}},
    {599,
     {"Network Connect Timeout Error",
      "This status code is not specified in any RFCs, but is used by some "
      "HTTP proxies to signal a network connect timeout behind the proxy "
      "to a client in front of the proxy.",
      "https://httpstatuses.io/599"}},
};

/// STDOUT messages

static constexpr std::string_view invalid_num_arguments =
    "Error: Invalid number of arguments given.\n";

static constexpr std::string_view invalid_code =
    "Error: Invalid HTTP status code.\n";

static constexpr std::string_view invalid_category =
    "Error: Invalid HTTP status category name. Valid names are informational, "
    "success, redirection, client-error, and server-error.\n";

static constexpr std::string_view usage = "Usage: httpcode <code>\n";

/// Utility functions

tl::expected<int, std::exception> to_digit(std::string_view s) noexcept {
  try {
    return std::stoi(std::string(s));
  } catch (const std::exception& e) {
    return tl::make_unexpected(e);
  }
}

std::string format_output(unsigned int code, std::string_view short_desc,
                          std::string_view long_desc,
                          std::string_view learn_more_url) noexcept {
  std::ostringstream oss;
  oss << code << " " << short_desc << '\n'
      << long_desc << "\n\n"
      << "Learn more: " << learn_more_url << '\n';
  return oss.str();
}

std::string list_all_codes() noexcept {
  std::ostringstream oss;
  oss << "HTTP Status Codes:\n";
  for (const auto& [code, desc] : codes) {
    const auto& [short_desc, _1, _2] = desc;
    oss << code << " " << short_desc << '\n';
  }
  return oss.str();
}

tl::expected<std::string, std::exception> list_all_codes_for_category(
    std::string_view category) noexcept {
  std::ostringstream oss;
  std::map<unsigned int, description>::const_iterator lo;
  std::map<unsigned int, description>::const_iterator hi;
  if (category == "informational") {
    lo = codes.lower_bound(100);
    hi = codes.upper_bound(199);
    oss << "HTTP Status Codes – Informational:\n";
  } else if (category == "success") {
    lo = codes.lower_bound(200);
    hi = codes.upper_bound(299);
    oss << "HTTP Status Codes – Success:\n";
  } else if (category == "redirection") {
    lo = codes.lower_bound(300);
    hi = codes.upper_bound(399);
    oss << "HTTP Status Codes – Success:\n";
  } else if (category == "client-error") {
    lo = codes.lower_bound(400);
    hi = codes.upper_bound(499);
    oss << "HTTP Status Codes – Client Error:\n";
  } else if (category == "server-error") {
    lo = codes.lower_bound(500);
    hi = codes.upper_bound(599);
    oss << "HTTP Status Codes – Server Error:\n";
  } else {
    return tl::make_unexpected(std::invalid_argument("Invalid category name."));
  }

  for (; lo != hi; ++lo) {
    const auto& [code, info] = *lo;
    const auto& [short_desc, _1, _2] = info;
    oss << code << " " << short_desc << '\n';
  }

  return oss.str();
}

}  // namespace httpcode

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cerr << httpcode::invalid_num_arguments;
    std::cerr << httpcode::usage;
    return 1;
  }

  const std::string_view arg1 = argv[1];
  const auto code = httpcode::to_digit(arg1);
  if (code.has_value() && httpcode::codes.contains(*code)) {
    const auto& [short_desc, long_desc, url] = httpcode::codes.at(*code);
    std::cout << httpcode::format_output(*code, short_desc, long_desc, url);
    return 0;
  } else if (code.has_value()) {
    std::cerr << httpcode::invalid_code;
    std::cerr << httpcode::usage;
    return 1;
  }

  if (arg1 == "list" && argc == 3) {
    const std::string_view category = argv[2];
    const auto output = httpcode::list_all_codes_for_category(category);
    if (!output.has_value()) {
      std::cerr << httpcode::invalid_category;
    }
    std::cout << *output;
    return 0;
  } else if (arg1 == "list") {
    std::cout << httpcode::list_all_codes();
    return 0;
  } else {
    std::cerr << "Error: Invalid command " << arg1 << '\n';
    std::cerr << httpcode::usage;
  }
}
