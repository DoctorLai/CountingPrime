using System;
using System.Linq;

namespace csharpprime
{
    public class Program
    {
        public const int Limit = 10000000;

        public static void Main(string[] args)
        {
            var startTime = Environment.TickCount;
            var serial = Serial(1, Limit);
            var serialMs = Environment.TickCount - startTime;

            startTime = Environment.TickCount;
            var parallel = Parallel(1, Limit);
            var parallelMs = Environment.TickCount - startTime;

            Console.WriteLine($"{serial}({serialMs}), {parallel}({parallelMs})");
        }

        public static bool IsPrime(int number)
        {
            if (number <= 1)
                return false;

            var end = (int)Math.Floor(Math.Sqrt(number));
            for (var index = 2; index <= end; index++)
                if (number % index == 0)
                    return false;

            return true;
        }

        public static int Serial(int start, int end) =>
            Enumerable.Range(start, end - start)
                      .Count(IsPrime);

        public static int Parallel(int start, int end) =>
            Enumerable.Range(start, end - start)
                      .AsParallel()
                      .Count(IsPrime);
    }
}
