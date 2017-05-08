using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CommandLine;
using CommandLine.Text;

namespace ImageConverter
{
    public class CLI
    {
        [Option('i', "inputFile", Required = true, HelpText = "File to process, required")]
        public string InputFile { get; set; }
        [Option('o', "outputFile", Required = false, HelpText = "Output file, if not set will be dat or .h")]
        public string OutputFile { get; set; }
        [Option('d', "datFile", Required = false, DefaultValue = true, HelpText = "Create a dat file for reading from SD (Default)")]
        public bool CreateDat { get; set; }
        [Option('h', "header", Required = false, HelpText = "Create header for compiling")]
        public bool CreateHeader { get; set; }

        [ParserState]
        public IParserState LastParserState { get; set; }

        [HelpOption]
        public string GetUsage()
        {
            return HelpText.AutoBuild(this, (HelpText current) => HelpText.DefaultParsingErrorsHandler(this, current));
        }
    }
}
