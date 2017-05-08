using System;
using System.Collections.Generic;
using System.IO;
using System.Drawing;
using System.Text;

namespace ImageConverter
{
    public static class Converter
    {
        public static bool ConvertToDat(string inputFile, string outputFile)
        {
            if(string.IsNullOrWhiteSpace(outputFile))
            {
                outputFile = Path.ChangeExtension(inputFile, ".dat");
            }
            if(!File.Exists(inputFile))
            {
                Console.WriteLine("File: " + inputFile + " does not exist.  Exiting...\n\n\n");
                return false;
            }
            Bitmap inputImage = (Bitmap)Image.FromFile(inputFile);
            int height = inputImage.Height;
            int width = inputImage.Width;
            BinaryWriter bw = new BinaryWriter(new FileStream(outputFile, FileMode.Create));
            byte[] byteArray = new byte[2];

            for (int y=0; y<height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    Color clr = inputImage.GetPixel(x, y);
                    UInt16 rgb = (UInt16) ((clr.B % 32) + ((clr.G % 64) << 6) + ((clr.R % 32) << 11));
                    byteArray[0] = (byte)rgb;
                    byteArray[1] = (byte)(rgb >> 8);
                    bw.Write(byteArray);
                }
            }

            bw.Close();
            Console.WriteLine("Finished converting file\nSize: ("+width+","+height+")");
            return true;
        }        

        public static string ByteArrayToString(byte[] ba)
        {
            StringBuilder hex = new StringBuilder(ba.Length * 2);
            foreach (byte b in ba)
                hex.AppendFormat("{0:x2}", b);
            return hex.ToString();
        }

        public static bool ConvertToHeader(string inputFile, string outputFile)
        {
            if (string.IsNullOrWhiteSpace(outputFile))
            {
                outputFile = Path.ChangeExtension(inputFile, ".h");
            }
            string varName = Path.GetFileNameWithoutExtension(outputFile);

            if (!File.Exists(inputFile))
            {
                Console.WriteLine("File: " + inputFile + " does not exist.  Exiting...\n\n\n");
                return false;
            }

            StreamWriter headerFile = null;
            try
            {
                headerFile = new StreamWriter(outputFile);
            } catch(Exception e)
            {
                Console.WriteLine("Exception in writing header file: " + e.Message);
                Console.WriteLine("Exiting\n\n\n");
                return false;
            }

            headerFile.WriteLine("const uint16_t " + varName + "[] PROGMEM = {");
            Bitmap inputImage = (Bitmap)Image.FromFile(inputFile);
            int height = inputImage.Height;
            int width = inputImage.Width;
            int rowCounter = 0;
            byte[] byteArray = new byte[2];
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    Color clr = inputImage.GetPixel(x, y);
                    UInt16 rgb = color565(clr);
                    
                    if (rowCounter < 5)
                    {
                        if (y == height - 1 && x == width - 1)
                            headerFile.Write(rgb);
                        else
                            headerFile.Write(rgb + ", ");
                    } else
                    {
                        if (y == height - 1 && x == width - 1)
                            headerFile.Write(rgb);
                        else
                            headerFile.WriteLine(rgb + ", ");
                        rowCounter = -1;
                    }
                    rowCounter++;
                }
            }
            headerFile.WriteLine(" };");
            headerFile.Close();
            Console.WriteLine("Finished converting file\nSize: (" + width + "," + height + ")"); 
            return true;
        }
        
        public static UInt16 color565(Color clr)
        {
            return (UInt16)(((clr.ToArgb() & 0xF8) << 8) | ((clr.ToArgb() & 0xFC) << 3) | (clr.ToArgb() >> 3));

        }
    }        
}
