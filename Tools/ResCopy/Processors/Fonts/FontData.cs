using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace ResCopy
{
    internal class FontData
    {
        public string Name { get; private set; }

        public string Style { get; private set; }

        public int Size { get; private set; }

        public string Alphabet { get; private set; }

        public static FontData Load(string fileName)
        {
            var res = new FontData();

            var document = XDocument.Load(fileName);
            res.Name = GetAttributeValue(document.Root, "Name");
            res.Style = GetAttributeValue(document.Root, "Style", "Regular");
            res.Size = int.Parse(GetAttributeValue(document.Root, "Size"));
            res.Alphabet = GetAttributeValue(document.Root, "Alphabet");

            return res;
        }

        private static string GetAttributeValue(XElement elem, XName attrName)
        {
            var attr = elem.Attribute(attrName);

            if (attr == null)
            {
                throw new InvalidOperationException(string.Format("{0} element must have {1} attribute.", elem.Name, attrName));
            }

            return attr.Value;
        }

        private static string GetAttributeValue(XElement elem, XName attrName, string defaultValue)
        {
            var attr = elem.Attribute(attrName);

            if (attr == null)
            {
                return defaultValue;
            }

            return attr.Value;
        }
    }
}