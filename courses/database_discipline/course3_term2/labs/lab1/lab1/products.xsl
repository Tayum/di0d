<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl=
  "http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml"
  doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"
  doctype-public="-//W3C//DTD XHTML 1.1//EN" indent="yes"/>

  <xsl:template match="/">
    <html>
      <head>
        <title>
          The Products Table
        </title>
      </head>
      <body>
        <h1>
          The Products Table
        </h1>
        <table>
          <tr>
            <td>Name</td>
            <td>From</td>
            <td>To</td>
            <td>Description</td>
          </tr>
          <xsl:apply-templates/>
        </table>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="item">
    <tr>
     <td>
         <xsl:value-of select="title"/>
         <br/>
         <xsl:element name="img">
             <xsl:attribute name="src">
                 <xsl:value-of select="img"/>
             </xsl:attribute>
         </xsl:element>
     </td>
     <td><xsl:value-of select="price_from"/></td>
     <td><xsl:value-of select="price_to"/></td>
     <td><xsl:value-of select="desc"/></td>
    </tr>
  </xsl:template>

</xsl:stylesheet>