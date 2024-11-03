// C#链表
// 2024-11-03

using System;
using System.Collections.Generic;

namespace HelloWorldApplication
{
    class HelloWorld
    {
        static void PrintNameList(LinkedList<string> list)
        {
            Console.Write("nameList: ");
            foreach (var name in list)
            {
                Console.Write("{0} ", name);
            }
            Console.WriteLine("");
        }

        static int LinkedListLength(LinkedList<string> list)
        {
            int length = 0;

            foreach (var node in list)
            {
                length++;
            }
            return length;
        }

        static bool IsNameExisted(LinkedList<string> list, string name)
        {
            foreach (var node in list)
            {
                if (node == name)
                {
                    return true;
                }
            }
            return false;
        }

        static void TestLinkedList()
        {
            var nameList = new LinkedList<string>();
            nameList.AddFirst("Tom");
            nameList.AddFirst("Bob");
            nameList.AddFirst("Jerry");

            PrintNameList(nameList);
            Console.WriteLine("list length: {0}", LinkedListLength(nameList));

            if (IsNameExisted(nameList, "Tom"))
            {
                Console.WriteLine("name \"Tom\" is existed in nameList");
            }
            if (!IsNameExisted(nameList, "Alice"))
            {
                Console.WriteLine("name \"Alice\" is not existed in nameList");
            }
            nameList.Remove("Bob");
            PrintNameList(nameList);
        }

        static void Main(string[] args)
        {
            TestLinkedList();
        }
    }
}
