using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace ResCopy
{
    internal enum BaseUniformType
    {
        None = 0,
        Boolean = 1,
        Integer = 2,
        Float = 3,
        Sampler = 4
    }

    internal class UniformType
    {
        public UniformType(string typeName)
        {
            ArraySize = -1;
            MDimension = -1;
            NDimension = -1;

            var res = Regex.Match(typeName, @"^([a-zA-Z0-9]+)\[([0-9]+)\]$");

            var baseType = typeName;

            if (res.Success)
            {
                baseType = res.Groups[1].Value;
                ArraySize = int.Parse(res.Groups[2].Value);
            }

            res = Regex.Match(baseType, @"^([bi]?)vec([2-4])$");

            if (res.Success)
            {
                switch (res.Groups[1].Value)
                {
                    case "b": BaseType = BaseUniformType.Boolean; break;
                    case "i": BaseType = BaseUniformType.Integer; break;
                    default: BaseType = BaseUniformType.Float; break;
                }

                NDimension = int.Parse(res.Groups[2].Value);
                return;
            }

            res = Regex.Match(baseType, @"^mat([2-4])(?:x([2-4]))?$");

            if (res.Success)
            {
                BaseType = BaseUniformType.Float;
                NDimension = int.Parse(res.Groups[1].Value);

                if (!string.IsNullOrWhiteSpace(res.Groups[2].Value))
                {
                    MDimension = int.Parse(res.Groups[2].Value);
                }
                else
                {
                    MDimension = NDimension;
                }
                return;
            }

            switch (baseType)
            {
                case "float": BaseType = BaseUniformType.Float; break;
                case "int": BaseType = BaseUniformType.Integer; break;
                case "bool": BaseType = BaseUniformType.Boolean; break;
                case "sampler2D": BaseType = BaseUniformType.Sampler; break;
                case "struct":
                    throw new Exception(string.Format("Uniform structures are not supported :(", baseType));
                default:
                    throw new Exception(string.Format("Unknown type: {0}", baseType));
            }
        }

        public BaseUniformType BaseType { get; private set; }

        public int NDimension { get; private set; }

        public int MDimension { get; private set; }

        public int ArraySize { get; private set; }

        public void WriteTo(BinaryWriter writer)
        {
            writer.Write((byte)BaseType);
            writer.Write((byte)NDimension);
            writer.Write((byte)MDimension);
            writer.Write((byte)ArraySize);
        }
    }
}