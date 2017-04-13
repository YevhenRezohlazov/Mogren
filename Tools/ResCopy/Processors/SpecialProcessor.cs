using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ResCopy
{
    public abstract class SpecialProcessor
    {
        private string[] _resExtensions;

        public SpecialProcessor(params string[] resExtensions)
        {
            _resExtensions = resExtensions;
        }

        public string[] ResExtensions
        {
            get
            {
                return _resExtensions;
            }
        }

        /// <summary>
        ///
        /// </summary>
        /// <param name="srcResPath"></param>
        /// <param name="destDirPath"></param>
        /// <returns>Output file name.</returns>
        public abstract string Process(string srcResPath, string destDirPath);
    }
}