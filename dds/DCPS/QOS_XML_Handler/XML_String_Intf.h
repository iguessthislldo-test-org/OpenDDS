//==============================================================
/**
 *  @file  XML_String_Intf.h
 *
 *
 *  @author Danilo C. Zanella (dczanella@gmail.com)
 */
//================================================================

#ifndef OPENDDS_DCPS_QOS_XML_HANDLER_XML_STRING_INTF_H
#define OPENDDS_DCPS_QOS_XML_HANDLER_XML_STRING_INTF_H
#include /**/ "ace/pre.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "dds_qos.hpp"
#include "XML_Intf.h"
#include "dds/DdsDcpsInfrastructureC.h"
#include "OpenDDS_XML_QOS_Handler_Export.h"

namespace XML
{
  struct Environment_Resolver;
  template <typename Resolver>
  class XML_Schema_Resolver;
  class XML_Error_Handler;
}

namespace XERCES_CPP_NAMESPACE {
  class XercesDOMParser;
  class DOMDocument;
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL

namespace OpenDDS {
namespace DCPS {

  class OpenDDS_XML_QOS_Handler_Export QOS_XML_String_Handler :
    public QOS_XML_Handler
  {
  public:
    /// Pass an optional @error_handler which is called back when
    /// there are any errors parsing the input XML. The QOS_XML_String_Handler
    /// will assume ownership when a pointer is passed
    explicit QOS_XML_String_Handler(XML::XML_Error_Handler* error_handler = 0);

    ~QOS_XML_String_Handler();

    /**
     * The init method will open the file and will validate
     * it against the schema. It returns RETCODE_ERROR
     * when any error occurs during parsing
     */
    DDS::ReturnCode_t
    init(const ACE_TCHAR * membuf);

    /**
     * add_search_path will add a relative path to the XML
     * parsing library. The XML parsing library will use
     * this path to search for the schema
     */
    void
    add_search_path(const ACE_TCHAR *environment,
                    const ACE_TCHAR *relpath);

  private:
    /// Schema resolver
    XML::XML_Schema_Resolver<XML::Environment_Resolver> * res_;

    /// Error handler
    XML::XML_Error_Handler * eh_;

    /// Parser
    XERCES_CPP_NAMESPACE::XercesDOMParser * parser_;

    /// Final DOMDocument that should be passed to
    /// dds::reader::dds method
    XERCES_CPP_NAMESPACE::DOMDocument * finalDoc_;
  };
}
}

OPENDDS_END_VERSIONED_NAMESPACE_DECL

#include /**/ "ace/post.h"

#endif /* DCPS_CONFIG_XML_STRING_INTF_H */
