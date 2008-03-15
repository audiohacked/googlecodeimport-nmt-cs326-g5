"""
XMLFilter.py

XMLFilter provides a SAX-compatibile interface for parsing, filtering,
and/or regenerating XML files. By falling back to the pure-Python xmllib
behind the scenes, it works even if your copy of Python doesn't have a
real XML parser such as expat.

Copyright Andrew Shearer 2003
<mailto:ashearer@shearersoftware.com>
See http://www.shearersoftware.com/ for the current version.

License: dual-licensed under the Python License and MPSL 1.1 (Mozilla license).

To use this compatibility code in your own program, inherit your parser
class from XMLFilter.XMLSAXHandler instead of the usual
xml.sax.ContentHandler, and it will automatically work whether or not
expat does. No other changes should be necessary.

To filter XML output as it goes to another XMLSAXHandler, subclass
XMLFilter.XMLFilter. Call the superclass methods to pass the event
along. For example:

    class MyFilter(XMLFilter.XMLFilter):
        def endElement(self, tag):
            if myFilteringTest():
                XMLFilter.XMLFilter.endElement(self, tag)

You can modify the SAX event stream instead by calling the other
superclass methods.

When you initialize an XMLFilter, you give it a "next" handler in the
chain. An ideal endpoint is XMLFilter.XMLGenerator, which recreates the
input stream as closely as possible. (There are some caveats preventing
byte-for-byte equality, though the meaning will be the same: attributes
may be in a different order, and Python's xml.sax parsers suppress
comments. That's one advantage of xmllib: it's older and slower, but it
passes comments along.)

Use the following functions:

import sys, XMLFilter
handler = XMLFilter.XMLGenerator(sys.stdout)
XMLFilter.parseURL("http://www.shearersoftware.com/personal/weblog/rss.xml",
    handler, features = {XMLFilter.feature_namespaces: 1})
XMLFilter.parseFilePath(myFilePath, handler)
XMLFilter.parseStream(open(myFile, 'r'), handler)

The optional "features" parameter (available in all the "parse"
functions) contains a dict of features to be turned on or off, including
namespaces. If namespaces are turned on, namespace URIs will be sent to
your handler, using startElementNS instead of startElement, for example.

Note: unless you specifically turn the feature off, expat may try to
resolve an external DTD, which means loading a URL and may have side
effects or cause parsing to fail in the absence of an Internet
connection. To avoid this, if you know the document is standalone
(meaning that it can be interpreted the same way with or without the
DTD) make sure feature_external_ges is set to 0. Might as well set the
similar flag feature_external_pes to 0 at the same time, though the
current default as of this writing appears to be 0 (and expat doesn't
support it being turned on anyway).

XMLGenerator has extensive namespace support. In addition to recognizing
the SAX beginPrefixMapping and endPrefixMapping calls for namespaces, if
your code gives it an element in an undeclared namespace, it will work
out the desired prefix from the qname parameter and take care of
declaring it for you. (If the namespace has already been declared, it
will use the declared prefix no matter what the qname parameter.)

The xmllib adapter has been designed for event-by-event compatibility
with xml.sax.

XMLSAXReader also supports a feature that helps output CDATA-quoted
sections, though it's transparent to your program if you don't use it.
(xmllib allows the parser to recognize CDATA sections so they are
preserved through to XMLGenerator.)

Sample of generating a complete document, using setCDataHint:
>>> import StringIO,sys
>>> myoutput = StringIO.StringIO()
>>> handler = XMLGenerator(myoutput)
>>> handler.startDocument()
>>> handler.startElement('root', {})
>>> handler.setCDataHint(1)
>>> handler.characters("I'm using < and > with <b>impunity</b>. I can even talk about <[!CDATA[, the CDATA start marker, and ]]>, the end marker, without it blowing up.")
>>> handler.setCDataHint(0)
>>> handler.endElement('root')
>>> handler.endDocument()
>>> print myoutput.getvalue()
<?xml version="1.0" encoding="utf-8"?>
<root><![CDATA[I'm using < and > with <b>impunity</b>. I can even talk about <[!CDATA[, the CDATA start marker, and ]]]><![CDATA[]>, the end marker, without it blowing up.]]></root>

Now we read in the same file, just to make sure it's parseable.
>>> myoutput.seek(0)
>>> otheroutput = StringIO.StringIO()
>>> otherhandler = XMLGenerator(otheroutput)
>>> parseStream(myoutput, otherhandler)
>>> print otheroutput.getvalue()
<?xml version="1.0" encoding="utf-8"?>
<root>I'm using &lt; and &gt; with &lt;b&gt;impunity&lt;/b&gt;. I can even talk about &lt;[!CDATA[, the CDATA start marker, and ]]&gt;, the end marker, without it blowing up.</root>

Revision History:

2003-09-04 1.1 Andrew Shearer

Added a "features" dict as a parameter to the parse methods, replacing the
"namespaces" boolean parameter.
The dict contains booleans values for keys such as feature_namespaces,
feature_namespace_prefixes, feature_external_ges, and feature_external_pes,
all of which are defined in the XMLFilter namespace.
feature_namespaces and feature_namespace_prefixes are recognized by xmllib.
Other keys are ignored, which is usually the correct behavior.
All features are recognized by xml.sax.


2003-07-06 1.0 Andrew Shearer

Moved code out of rssweblog.py. Extensive changes for SAX and namespace
compatibility. Encoding support for input and output, docstrings, and
doctests. parseURL, parseFilePath, and parseStream functions. Python
1.5.2 compatibility. setCDataHint model for CDATA support compatible
with existing xml.sax ContentHandler code. Simplified method for
detecting whether it's necessary to fall back to xmllib.

xmllib compatibility: namespace support for attributes, master namespace
switch to match xml.sax, input encoding support, test suite (in
XMLFilterTest) proves event-for-event compatibility with xml.sax.

XMLGenerator: renamed from XMLWriter to match xml.sax.saxutils; improved
implicit and explicit namespace support; output encoding support with
Python 2.3 optimization (xmlcharrefreplace feature is used if
available).

"""
import string

class Error(Exception):
    pass

class NamespaceError(Error):
    pass

use_sax = 1
# true value to try modern xml.sax library; will be busted down to false if only
# the older xmllib is available (i.e. Python is missing expat support, as in
# the factory-default Python 2.2 in Mac OS X 10.2)

try:
    if not use_sax: raise ImportError
    import xml.sax.handler
    feature_namespaces = xml.sax.handler.feature_namespaces
    feature_namespace_prefixes = xml.sax.handler.feature_namespace_prefixes
    feature_external_pes = xml.sax.handler.feature_external_pes
    feature_external_ges = xml.sax.handler.feature_external_ges
    class XMLSAXHandler(xml.sax.handler.ContentHandler):
        def setCDataHint(self, flag):   # not in SAX
            pass
        
        def comment(self, data):        # not in SAX
            pass
            
except ImportError:
    use_sax = 0
    feature_namespaces = "http://xml.org/sax/features/namespaces" 
    feature_namespace_prefixes = "http://xml.org/sax/features/namespace-prefixes" 
    feature_external_ges = "http://xml.org/sax/features/external-general-entities" 
    feature_external_pes = "http://xml.org/sax/features/external-parameter-entities" 

    class XMLSAXHandler:
        """defines our xml.sax and xmllib-compatible xml handler.
        Intended to be subclassed. A direct instance will ignore all input (which is
        useful as the destination of an xmlFilter, similar to piping to /dev/null)
        """
        def __init__(self):
            pass
        
        def startDocument(self): #, encoding, standalone):
            pass
        
        def processingInstruction(self, target, data):
            pass
        
        def comment(self, data):    # not in SAX
            pass
        
        def startElementNS(self, nameTuple, qname, attrs):
            pass
        
        def endElementNS(self, nameTuple, qname):
            pass
        
        def startPrefixMapping(self, prefix, uri):
            pass
        
        def endPrefixMapping(self, prefix):
            pass
        
        def characters(self, data):
            pass
        
        def ignorableWhitespace(self, data):
            pass
        
        def setCDataHint(self, flag):   # not in SAX
            pass
        
        def setEnclosingNewlinesHint(self, flag):
            pass

        def endDocument(self):
            pass

# Turns out we can't use saxutils' XMLGenerator; in Python 2.2 it's buggy
# (startElementNS throws an exception when it tries to output an unqualified
# attribute)
pythonSupportsEncodeMethod = hasattr('', 'encode')
def escape(data, forattribute = 1):
    """Escape data for writing to an XML stream in the given encoding
    (if we are using a Python with encode method support (>= 2.0), otherwise
    ignore encoding parameter)."""
    data = string.replace(data, "&", "&amp;")
    data = string.replace(data, "<", "&lt;")
    data = string.replace(data, ">", "&gt;")
    if forattribute: data = string.replace(data, '"', "&quot;")
    return data

class XMLGenerator(XMLSAXHandler):
    """Accepts SAX-like events and writes an XML file. The opposite of an XML parser.
    Typical endpoint of an XMLFilter chain."""
    def __init__(self, out, encoding = 'utf-8'):
        self._out = out
        self._encoding = encoding
        self._cDataHint = 0
        self.__namespacesByURI = {}
        self.__namespacesByPrefix = {}
        self.__newNamespaces = []
        self.__implicitNamespaceStack = None
        self.__previousPrefixMapping = {}
        self.__haveTriedInstallingEncoder = 0
        self.__useXMLCharrefReplace = 0 # Python 2.3 feature; will be turned on if available
        # (pre-Python 2.3, we fall back on the slow char-by-char method of handling encoding errs)
        XMLSAXHandler.__init__(self)
    
    if pythonSupportsEncodeMethod:
        def _write(self, data, allowcharrefs = 1):
            if self.__useXMLCharrefReplace:
                # Take advantage of Python 2.3 feature that quickly
                # encodes XML character references for us if the
                # output encoding can't represent some chars directly
                if allowcharrefs:
                    self._out.errors = 'xmlcharrefreplace'
                else:
                    self._out.errors = 'strict'
                self._out.write(data)
            elif allowcharrefs:
                try:
                    self._out.write(data)
                except UnicodeError:
                    # Couldn't convert the Unicode string to the desired encoding,
                    # so resort to Unicode entities.
                    # This simple implementation retries character-by-character, because the
                    # Python 2.0 Unicode API doesn't say where the error was.
                    out = self._out # local var optimization
                    for ch in data:
                        try:
                            out.write(ch)
                        except UnicodeError:
                            out.write('&#%d;' % ord(ch))
            else:
                # Rely on the stream's encoder
                self._out.write(data)
    else:
        def _write(self, data, allowcharrefs = 1):
            # This Python has no Unicode support, so just pass the
            # data through and hope for the best (which would be that
            # the output encoding matches the input encoding).
            self._out.write(data)
        
    def startDocument(self):
        if pythonSupportsEncodeMethod and not self.__haveTriedInstallingEncoder:
            # delay installing the encoder until now so that clients have a chance to
            # change self._encoding up until the time the document actually starts
            try:
                import codecs
            except ImportError:
                pass
            else:
                self._out = codecs.lookup(self._encoding)[3](self._out)
                # For Python 2.0 compatibility, don't use codecs.getwriter
                if hasattr(codecs, 'xmlcharrefreplace_errors'):
                    # Check for Python 2.3 feature
                    self.__useXMLCharrefReplace = 1
            self.__haveTriedInstallingEncoder = 1           
        self._write('<?xml version="1.0" encoding="%s"?>\n' % self._encoding)
        XMLSAXHandler.startDocument(self)
    
    def startPrefixMapping(self, prefix, uri):
        #print 'started prefix mapping', prefix, uri
        prefix = prefix or ''
        previousURIForPrefix = self.__namespacesByPrefix.get(prefix)
        savedState = (
            previousURIForPrefix, self.__namespacesByURI.get(uri),
            self.__previousPrefixMapping.get(prefix))
        self.__previousPrefixMapping[prefix] = savedState
        if previousURIForPrefix and self.__namespacesByURI.get(previousURIForPrefix) == prefix:
            # this prefix overrides a previous instance of the same prefix;
            # remove the old URI since it's no longer accessible
            # +++ FIX: this may make a valid namespace URI inaccessible in some
            # unusual conditions: multiple prefixes for the same URI, one
            # of which is later overridden with a different URI.
            # Need to add a test case for this.
            self.__namespacesByURI[previousURIForPrefix] = None
        self.__namespacesByURI[uri] = prefix
        self.__namespacesByPrefix[prefix] = uri
        self.__newNamespaces.append((prefix, uri)) # buffer new namespace events to be processed by startElement
    
    def endPrefixMapping(self, prefix):
        #print 'ending prefix mapping', prefix
        prefix = prefix or ''
        savedState = self.__previousPrefixMapping.get(prefix)
        if not savedState:
            raise NamespaceError, 'endPrefixMapping called without matching startPrefixMapping for prefix "%s"' % prefix
        else:
            # revert everything to the way it was before startPrefixMapping was called
            # (except None will be in the _namespace dicts instead of a missing value, but that's OK)
            # +++ CHECK: does this work correctly if there are multiple prefixes defined
            # in the same startPrefixMapping batch pointing to the same URI, and
            # the endPrefixMapping calls are out of order (which is legal)?
            # The test suite hasn't hit this possibility yet.
            uri = self.__namespacesByPrefix[prefix]
            previousURIForPrefix, self.__namespacesByURI[uri], self.__previousPrefixMapping[prefix] = savedState
            self.__namespacesByPrefix[prefix] = previousURIForPrefix
            if previousURIForPrefix:
                self.__namespacesByURI[previousURIForPrefix] = prefix
            if self.__newNamespaces:
                # There were still xmlns attributes pending write. This could
                # happen if an entire element is filtered out upstream but the
                # empty startPrefixMapping()/endPrefixMapping() pair is left in.
                # Clean up the pending namespaces if this one is among them.
                try:
                    self.__newNamespaces.remove((prefix, uri))
                except ValueError:
                    pass    # OK if it wasn't found
    
    def comment(self, data):
        self._write('<!--%s-->' % data, 0)
        
    def processingInstruction(self, target, data):
        self._write('<?%s %s?>' % (target, data), 0)
    
    def _tupleToQName(self, nameTuple, default = ''):
        qname = default
        nsuri = nameTuple[0]
        if nsuri:
            # handle namespace URIs
            predeclaredPrefix = self.__namespacesByURI.get(nsuri)
            if predeclaredPrefix is None:
                if qname and string.find(qname, ':') > 0:
                    # Found a new namespace that somehow wasn't reported to us
                    # through startPrefixMapping. Take the prefix from the qname.
                    # Store it in a stack so we will know when to remove it.
                    prefix = qname[:string.find(qname, ':')]
                    if self.__implicitNamespaceStack:
                        self.__implicitNamespaceStack[-1].append(prefix)
                    else:
                        self.__implicitNamespaceStack = [[prefix]]
                    self.startPrefixMapping(prefix, nsuri)
                else:
                    # Error - unknown namespace URI, and no qname to
                    # fix it with. As a desperation measure, we could make
                    # up a random prefix, but at this point we just throw
                    # an error.
                    raise NamespaceError, "Unknown namespace URI %s. (Sending a qname will allow XMLGenerator to work around the problem.)" % nsuri
            elif predeclaredPrefix == '':
                qname = nameTuple[1]
            else:
                # make a valid qname for the current context; don't trust the one passed in
                # (the prefix might be a well-known default name and not the one in effect in
                # this document). The form is prefix:tagname.
                qname = predeclaredPrefix + ':' + nameTuple[1]
        elif not qname:
            qname = nameTuple[1]
        #if not qname:
        #    print "Missing qname for ",repr(nameTuple)
        return qname
        
    def startElement(self, name, attrs):
        parts = ['<', name]
        for key, value in attrs.items():
            parts.extend((' ', key, '="', escape(value, 1), '"'))
        parts.append('>')
        self._write(string.join(parts, ''), 1)
     
    def endElement(self, name):
        self._write('</%s>' % name)

    def startElementNS(self, nameTuple, qname, attrs):
        if self.__implicitNamespaceStack:
            self.__implicitNamespaceStack.append([])    # if we're doing implicit namespaces, keep stack in sync with tag depth
        qname = self._tupleToQName(nameTuple, qname)
        parts = ['<', qname]
        for key, value in attrs.items():
            key = self._tupleToQName(key)
            parts.extend([' ', key, '="', escape(value, 1), '"'])
        if self.__newNamespaces:
            for prefix, uri in self.__newNamespaces:
                if prefix:
                    parts.extend([' xmlns:', prefix])
                else:
                    parts.append(' xmlns')
                parts.extend(['="', escape(uri, 1), '"'])
            self.__newNamespaces = []
        parts.append('>')
        self._write(string.join(parts, ''))
     
    def endElementNS(self, nameTuple, qname):
        nsuri = nameTuple[0]
        if nsuri:    # try to convert namespace URI back to prefix
            predeclaredPrefix = self.__namespacesByURI.get(nsuri)
            if predeclaredPrefix is None:
                pass # use the passed-in qname when the namespace isn't declared
            elif predeclaredPrefix == '':
                qname = nameTuple[1]
            else:
                qname = predeclaredPrefix + ':' + nameTuple[1]
        elif nameTuple[1]:
            qname = nameTuple[1]
        #qname = self._tupleToQName(nameTuple, qname)
        self._write('</%s>' % qname)
        if self.__implicitNamespaceStack:       # if we're doing implicit namespaces, pop the end of the stack and restore
             for prefix in self.__implicitNamespaceStack.pop():
                self.endPrefixMapping(prefix)

    def characters(self, data):
        if self._cDataHint:
            # write CDATA-quoted content. Don't blow up if it contains ']]>'.
            cdatasections = data.split("]]>")   # Correct for embedded ]]>
            for dataindex in range(0, len(cdatasections)):
                data = cdatasections[dataindex]
                        
                self._write('<![CDATA[', allowcharrefs = 0)
                if dataindex > 0: self._write(']>', allowcharrefs = 0)
                self._write(data, allowcharrefs = 0)
                if dataindex < len(cdatasections) - 1: self._write(']', allowcharrefs = 0)
                self._write(']]>', allowcharrefs = 0)
        else:
            # write entity-escaped content
            self._write(escape(data, 0), allowcharrefs = 1)

    def ignorableWhitespace(self, data):
        self._write(data)
    
    def setCDataHint(self, flag):  # not in SAX: hint to use CDATA quoting rather than entity escaping
        self._cDataHint = flag
        
    def endDocument(self):
        if self.__implicitNamespaceStack:
            raise NamespaceError, "Internal error; unbalanced implicit namespaces: " + repr(self.__implicitNamespaceStack)
        XMLSAXHandler.endDocument(self)
    
def parseURL(url, handler, features = {}):
    import urllib
    stream = urllib.open(url)
    try:
        parseStream(stream, handler, features = features)
    finally:
        stream.close()

def parseFilePath(path, handler, features = {}):
    stream = open(path, 'r')
    try:
        parseStream(stream, handler, features = features)
    finally:
        stream.close()

def parseStream(infile, handler, features = {}):
    global use_sax
    if use_sax:
        try:
            _parseFileSAX(handler, infile, features)
        except xml.sax.SAXReaderNotAvailable:
            use_sax = 0
        else:
            return
    _parseFileXMLLib(handler, infile, features = features)

def _parseFileSAX(handler, infile, features):
    parser = xml.sax.make_parser()
    #handler.setEnclosingNewlinesHint(1)
    for featureName, featureValue in features.items():
        parser.setFeature(featureName, featureValue)
    parser.setContentHandler(handler)
    parser.parse(infile)
    #parser.close()

xmllib = None

def _parseFileXMLLib(handler, infile, features):
    global xmllib
    import xmllib
    class SAXAdapterForXMLLib(xmllib.XMLParser):
        def __init__(self, filter, expose_namespaces, encoding = 'utf-8', namespace_prefixes = 0):
            self._filter = filter
            self._encoding = encoding
            self._documentStarted = 0
            try:
                xmllib.XMLParser.__init__(self, accept_utf8 = (encoding == 'utf-8'))
            except (NameError, TypeError):
	            xmllib.XMLParser.__init__(self) # for Python 1.5
            #self._namespaceStack = [(self.getnamespace(), ())]    # xmllib starts off with an "xml" namespace predefined
            #self._filter.startDocument()
            #self._documentStarted = 1
            self.__expose_namespaces = expose_namespaces
            self.__namespace_prefixes = namespace_prefixes
            self.__suppressNextWhitespace = 0

        def handle_xml(self, encoding, standalone):
            if encoding: self._encoding = encoding
            if not self._documentStarted:
                self._filter.startDocument()
                self._documentStarted = 1
                self.__suppressNextWhitespace = 1
            pass
        
        def handle_doctype(self, tag, pubid, syslit, data):
            pass
        
        if hasattr('', 'decode'):
            def handle_data(self, data):
                if not data: return
                if not self._documentStarted:
                    self._filter.startDocument()
                    self._documentStarted = 1
                
                if not self.__suppressNextWhitespace or string.strip(data):
                    self.__suppressNextWhitespace = 0
                    self._filter.characters(data.decode(self._encoding))
            
        else:
            def handle_data(self, data):
                if not data: return
                if not self._documentStarted:
                    self._filter.startDocument()
                    self._documentStarted = 1
                if not self.__suppressNextWhitespace or string.strip(data):
                    self.__suppressNextWhitespace = 0
                    self._filter.characters(data)
            
        def handle_cdata(self, data):
            self._filter.setCDataHint(1)    # hint for the XML writer to quote using CDATA
            self.handle_data(data)
            self._filter.setCDataHint(0)    # reset hint (manual reset means that if a filter removes the character data entirely, this will still work)
        
        def handle_comment(self, data):
            self.__suppressNextWhitespace = 0
            if pythonSupportsEncodeMethod:
                data = data.decode(self._encoding)
            self._filter.comment(data)
        
        def handle_proc(self, name, data):
            if not self._documentStarted:
                self._filter.startDocument()
                self._documentStarted = 1
            self.__suppressNextWhitespace = 0
            if pythonSupportsEncodeMethod:
                data = data.decode(self._encoding)
            self._filter.processingInstruction(data)
        
        def unknown_starttag(self, tag, attrs):
            # tricky namespace handling here.
            # xmllib will have stripped xmlns attributes,
            # so we have to figure out what they were from xmllib's
            # stack, then trigger SAX startPrefixMapping calls.
            # Also, xmllib will have transformed the tag name
            # if it was in a namespace, so that 'prefix:tagname'
            # becomes 'uri tagname'. We transform it into
            # tuple form if expose_namespaces is on, tuple and 'prefix:tagname'
            # (qualified name, or qname) forms if namespace_prefixes is also on,
            # and 'prefix:tagname' form alone if expose_namespaces is off.
            # This matches the SAX behavior.
            if not self._documentStarted:
                self._filter.startDocument()
                self._documentStarted = 1
            self.__suppressNextWhitespace = 0
            if pythonSupportsEncodeMethod:
                tag = tag.decode(self._encoding)   # match xml.sax
            if self.__expose_namespaces:
                # Namespaced dispatch
                # First, take care of sending startPrefixMapping events
                if self.stack and self.stack[-1][1]:
                    # get the newly added namespace prefix declarations
                    for (prefix, uri) in self.stack[-1][1].items():
                        if pythonSupportsEncodeMethod:
                            prefix = prefix.decode(self._encoding)  # match xmllib
                            uri = uri.decode(self._encoding)
                        self._filter.startPrefixMapping(prefix, uri)
                # Fix up attribute names
                if attrs:
                    # translate xmllib's non-namespace attrs to SAX-standard namespaced
                    # attrs; change keys to tuples with a dummy URI (namely, None)
                    rawattrs = attrs
                    attrs = {}
                    for name, value in rawattrs.items():
                        tuple, qname = self._xmllibNameToTupleAndQName(name)
                        if pythonSupportsEncodeMethod:
                            value = value.decode(self._encoding)
                        attrs[tuple] = value
                # Fix up tag name
                tuple, qname = self._xmllibNameToTupleAndQName(tag)
                # Send startElementNS event
                self._filter.startElementNS(tuple, qname, attrs)
            else:
                # Non-namespace dispatch
                # Fix up attribute names
                if attrs:
                    # translate xmllib's 'uri tag' form to 'prefix:tag', if necessary,
                    # to match SAX behavior when namespace support is off
                    rawattrs = attrs
                    attrs = {}
                    for name, value in rawattrs.items():
                        if pythonSupportsEncodeMethod:
                            value = value.decode(self._encoding)
                        attrs[self._xmllibNameToQName(name)] = value
                # Fix up tag name
                tag = self._xmllibNameToQName(tag)
                # Send startElement event
                self._filter.startElement(tag, attrs)

        def _xmllibNameToTupleAndQName(self, tag):
            """Convert "uri tag" format to (uri, tag) and, optionally,
            "prefix:tag" formats. The latter is only returned if
            namespaces_prefixes is on, matching SAX behavior. The
            return format is ((nsuri, tag), qname).
            """
            splitPoint = string.find(tag, ' ')
            if splitPoint >= 0:
                # re-abbreviate namespace prefix
                nsuri = tag[:splitPoint]
                tag = tag[splitPoint+1:]
                if self.__namespace_prefixes:
                    return ((nsuri, tag), self.tupleToQName(nsuri, tag))
                else:
                    return ((nsuri, tag), None)
            else:
                if self.__namespace_prefixes:
                    return ((None, tag), tag)
                else:
                    return ((None, tag), None)
            
        def _xmllibNameToQName(self, tag):
            """Translate "uri tag" format to "prefix:tag" (but leave "tag" as "tag")
            """
            splitPoint = string.find(tag, ' ')
            if splitPoint >= 0:
                # re-abbreviate namespace prefix
                nsuri = tag[:splitPoint]
                tag = tag[splitPoint+1:]
                return self.tupleToQName(nsuri, tag)
            else:
                return tag
            
        def tupleToQName(self, nsuri, tag):
            """Translate nsuri and tag pair to "prefix:tag""
            """
            if not nsuri:
                return tag
            # walk xmllib's stack backwards, looking for the nsuri
            for stackIndex in range(len(self.stack)-1, -1, -1):
                for iterprefix, iteruri in self.stack[stackIndex][1].items():
                    if nsuri == iteruri:
                        if iterprefix:
                            return iterprefix + ':' + tag
                        else:
                            return tag
            raise NamespaceError, ('Unknown namespace URI %s' % nsuri)
        
        def unknown_endtag(self, tag):
            self.__suppressNextWhitespace = 0
            if pythonSupportsEncodeMethod:
                tag = tag.decode(self._encoding)   # match xml.sax
            if self.__expose_namespaces:
                # Namespace dispatch
                # Fix up tag name
                tuple, qname = self._xmllibNameToTupleAndQName(tag)
                # Send endElementNS event
                self._filter.endElementNS(tuple, qname)
                # Send endPrefixMapping events, if necessary
                expiringPrefixMappings = self.stack and self.stack[-1][1] or None #self._namespaceStack[-1][1]
                if expiringPrefixMappings:
                    for prefix in expiringPrefixMappings.keys():
                        if pythonSupportsEncodeMethod:
                            prefix = prefix.decode(self._encoding)  # match xmllib
                        self._filter.endPrefixMapping(prefix)
            else:
                # Non-namespace dispatch
                # Fix up tag name and send endElement event
                self._filter.endElement(self._xmllibNameToQName(tag))
            
        def close(self):
            self._filter.endDocument()
            xmllib.XMLParser.close(self)
            
    namespaces = features.get(feature_namespaces, 0)
    namespace_prefixes = features.get(feature_namespace_prefixes, not(namespaces))
    adapter = SAXAdapterForXMLLib(handler, expose_namespaces = namespaces, namespace_prefixes = namespace_prefixes)
    BUFSIZE = 2048
    while 1:
        buf = infile.read(BUFSIZE)
        if not buf: break
        adapter.feed(buf)
    adapter.close()


class XMLFilter(XMLSAXHandler):
    """Passes XML SAX-like events through to another XMLSAXHandler instance,
    forming a chain of instances. Subclasses will probably augment some
    of these methods in order to modify the XML stream.
    
    Can't use xml.sax.saxutils.XMLFilterBase because it has a bug
    in Python 2.2.0: it translates startElementNS to startElement."""
    def __init__(self, nextFilter):
        XMLSAXHandler.__init__(self)
        self._out = nextFilter
     
    def startDocument(self): #, encoding, standalone):
        self._out.startDocument()
        XMLSAXHandler.startDocument(self)
    
    #def xmlDeclaration(self, encoding, standalone):
    #    self._out.xmlDeclaration(encoding, standalone)
        
    def startPrefixMapping(self, prefix, uri):
        self._out.startPrefixMapping(prefix, uri)
    
    def endPrefixMapping(self, prefix):
        self._out.endPrefixMapping(prefix)
    
    def comment(self, data):    # not in SAX
        self._out.comment(data)
        
    def processingInstruction(self, target, data):
        self._out.processingInstruction(target, data)
    
    def startElement(self, name, attrs):
        self._out.startElement(name, attrs)
     
    def endElement(self, name):
        self._out.endElement(name)

    def startElementNS(self, nameTuple, qname, attrs):
        self._out.startElementNS(nameTuple, qname, attrs)
     
    def endElementNS(self, nameTuple, qname):
        self._out.endElementNS(nameTuple, qname)

    def characters(self, data):
        self._out.characters(data)
    
    def ignorableWhitespace(self, data):
        self._out.ignorableWhitespace(data)
    
    def setCDataHint(self, flag):  # not in SAX; handle CDATA content.
        self._out.setCDataHint(flag)
        
    def endDocument(self):
        XMLSAXHandler.endDocument(self)
        self._out.endDocument()
    
    def isDone(self):
        """should more data be withheld?"""
        return 0

def _test():
    import doctest, XMLFilter, sys
    doctest.testmod(XMLFilter, verbose = "-v" in sys.argv)
    print """Doctests are complete. For the full test suite, run TestXMLFilter.py
    from the directory containing the TestXMLFilterData directory."""

if __name__ == '__main__':
    _test()

