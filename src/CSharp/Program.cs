using System;
using System.Collections.Generic;
using System.IO;
using System.Diagnostics;

namespace FilesTraversal
{
    class ResultValue
    {
        public double time;
        public double degree;
        public int edgeNumber;
    }
    class Program
    {
        static void Main(string[] args)
        {
            RunTestCases();
            GenerateResult();
        }

        static void GenerateResult()
        {
            string testcaseFilePath = @"C:\Users\ssunah\testdata\degree";
            string resultFilePath = @"C:\Users\ssunah\testdata\degree_result";
            var allTestCaseFiles = GetAllTestCases(testcaseFilePath, "*_edges.csv");
            var allGroundTruthFiles = GetAllTestCases(testcaseFilePath, "*_truth.csv");
            var allTimeFile = GetAllTestCases(resultFilePath, "*.time");

            SortedDictionary<int, ResultValue> results = new SortedDictionary<int, ResultValue>();

            foreach (var edgesFile in allTestCaseFiles)
            {
                var number = Path.GetFileNameWithoutExtension(edgesFile).Split('_')[1];
                var truthFile = FindFile(allGroundTruthFiles, "_" + number + "_");
                var timeResultFile = FindFile(allTimeFile, "_" + number + "_");

                int vertexNumberResult = CountFileLines(truthFile);
                int edgeNumberResult = CountFileLines(edgesFile);
                double timeResult = ReadTime(timeResultFile);

                results[vertexNumberResult] = new ResultValue { time = timeResult, edgeNumber = edgeNumberResult, degree = edgeNumberResult / (double)vertexNumberResult };
            }

            using (var file = new StreamWriter(@"new_degree_result.txt"))
            {
                foreach (var result in results)
                {
                    file.Write(result.Key + ", ");

                }
                file.WriteLine();

                foreach (var result in results)
                {
                    file.Write(result.Value.edgeNumber + ", ");

                }
                file.WriteLine();

                foreach (var result in results)
                {
                    file.Write(result.Value.degree.ToString("0.00") + ", ");

                }
                file.WriteLine();

                foreach (var result in results)
                {
                    file.Write(result.Value.time + ", ");
                }

                file.WriteLine();
            }
        }
        static double ReadTime(string file)
        {
            using (StreamReader r = new StreamReader(file))
            {
                string line;
                while (!string.IsNullOrWhiteSpace( line = r.ReadLine()))
                {
                    return Double.Parse(line.Trim());
                }
            }

            return 0;
        }
        static string FindFile(string[] fileName, string number)
        {
            foreach (var file in fileName)
            {
                if (file.Contains(number))
                    return file;
            }

            return null;
        }
        static int CountFileLines(string fileName)
        {
            int count = 0;
            using (StreamReader r = new StreamReader(fileName))
            {
                while (!string.IsNullOrWhiteSpace(r.ReadLine()))
                {
                    count++;
                }
            }

            return count;
        }

        static void RunTestCases()
        {
            string testcaseFilePath = @"C:\Users\ssunah\testdata\degree";
            string resultFilePath = @"C:\Users\ssunah\testdata\degree_result";
            string executionFile = @"D:\CommunityDetection\x64\Release\CommunityDetection.exe";
            var allFiles = GetAllTestCases(testcaseFilePath, "*_edges.csv");

            foreach (var file in allFiles)
            {
                System.Console.WriteLine("------------------ Begin ------------------");
                System.Console.WriteLine(file);

                string argument = GenerateArgument(file, resultFilePath);
                ProcessStartInfo startInfo = new ProcessStartInfo(executionFile);
                startInfo.Arguments = argument;
                startInfo.CreateNoWindow = true;

                var process = Process.Start(startInfo);
                process.WaitForExit();
            }
        }

        static string[] GetAllTestCases(string filePath, string pattern)
        {
            return Directory.GetFiles(filePath, pattern);
        }

        static string GenerateArgument(string file, string resultFilePath)
        {
            string fileName = Path.GetFileNameWithoutExtension(file);
            string outputCommunitiesName = Path.Combine(resultFilePath, string.Format("{0}_communities.csv", fileName));
            string outputEdgesName = Path.Combine(resultFilePath, string.Format("{0}_edges.csv", fileName));
            string argument = string.Format("-A 0.5 0 {0} {1} {2} 10", file, outputCommunitiesName, outputEdgesName);
            return argument;
        }
        static void OutputGroundTruth(string fileName)
        {
            StreamWriter file = new System.IO.StreamWriter(fileName);

            int[] communities = { 3, 4, 5, 5, 6 };

            int vertexId = 0;

            int communityId = 1;

            for (int j = 0; j < 10; j++)
            {
                for (int i = 0; i < 500; i++)
                {
                    file.WriteLine(communityId + " " + vertexId);
                    vertexId++;
                }
                communityId++;
            }

            file.Close();
        }

        class Edge : IComparable<Edge>
        {
            public int X;
            public int Y;

            public int CompareTo(Edge other)
            {
                if (X.CompareTo(other.X) != 0)
                {
                    return X.CompareTo(other.X);
                }

                return Y.CompareTo(other.Y);
            }
        }

        static void ConvertToGroundTruth(string fileName, string newFileName)
        {
            string lines = File.ReadAllText(fileName);

            SortedDictionary<int, SortedSet<int>> dict = new SortedDictionary<int, SortedSet<int>>();

            int i = 0;
            foreach (var line in lines.Split('\n'))
            {
                if (string.IsNullOrWhiteSpace(line.Trim()))
                    continue;
                i++;

                if (!dict.ContainsKey(i))
                    dict[i] = new SortedSet<int>();
                foreach (var value in line.Split('\t'))
                {
                    if (string.IsNullOrEmpty(value.Trim()))
                        continue;
                    int vertex = int.Parse(value.Trim());
                    dict[i].Add(vertex);
                }
            }

            StreamWriter file = new System.IO.StreamWriter(newFileName);
            foreach (var community in dict)
            {
                foreach (var vertex in community.Value)
                {
                    file.WriteLine(community.Key + " " + vertex);
                }
            }
            file.Close();
        }

        static void ConvertToCSV(string fileName)
        {
            SortedSet<Edge> edges = new SortedSet<Edge>();
            string newFileName = Path.Combine(Path.GetDirectoryName(fileName), Path.GetFileNameWithoutExtension(fileName) + ".csv");
            string lines = File.ReadAllText(fileName);

            bool skipFirstLine = true;

            int iRow = 0;

            foreach (var line in lines.Split('\n'))
            {
                if (skipFirstLine)
                {
                    skipFirstLine = false;
                    continue;
                }

                int iColumn = 0;
                if (string.IsNullOrWhiteSpace(line.Trim()))
                    continue;
                foreach (var value in line.Split('\t'))
                {
                    if (string.IsNullOrEmpty(value.Trim()))
                        continue;
                    int linked = int.Parse(value.Trim());

                    if (linked == 1)
                    {
                        Edge edge = new Edge
                        {
                            X = iRow,
                            Y = iColumn
                        };

                        Edge inverseEdge = new Edge
                        {
                            X = iColumn,
                            Y = iRow
                        };

                        if (!edges.Contains(inverseEdge))
                        {
                            edges.Add(edge);
                        }
                    }

                    iColumn++;
                }

                iRow++;
            }

            StreamWriter file = new System.IO.StreamWriter(newFileName);
            foreach (var edge in edges)
                file.WriteLine(edge.X + " " + edge.Y);
            file.Close();
        }
    }
}
