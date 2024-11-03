// C# 字符串
// 2024-11-03

using System;

namespace HelloWorldApplication
{
    class HelloWorld
    {
        static void TestStringSplit()
        {
            Console.WriteLine("[TestStringSplit]: ---------------------------");

            string nameAll = "Tom;Bob;Jerry;Alice";
            string[] names = nameAll.Split(';');
            string nameNew = "";
            foreach (var n in names)
            {
                Console.WriteLine("name: {0}", n);
                nameNew += n + ";";
            }
            nameNew = nameNew.Substring(0, nameNew.Length - 1);
            Console.WriteLine("nameNew: {0}", nameNew);
        }

        static void Main(string[] args)
        {
            TestStringSplit();
        }
    }
}
