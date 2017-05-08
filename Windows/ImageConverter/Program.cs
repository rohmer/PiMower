using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using CommandLine;

namespace ImageConverter
{
    class Program
    {
        static void Main(string[] args)
        {
            var cli = new CLI();
            if (CommandLine.Parser.Default.ParseArguments(args, cli))
            {
                if (cli.CreateDat)
                    Converter.ConvertToDat(cli.InputFile, cli.OutputFile);
                if (cli.CreateHeader)
                    Converter.ConvertToHeader(cli.InputFile, cli.OutputFile);
            }   
        }        
    }
}
