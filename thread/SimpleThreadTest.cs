using System;
using System.Threading;

namespace ConsoleApplication {
	public class Top {	
		private int limit = 0;
		public void sayHello() {
			while(limit < 10) {
				Thread th= Thread.CurrentThread;
				Console.WriteLine("Thread " + th.GetHashCode() + ": " + limit++);
			}
		}
	}

	class SimpleThreadTest {
		static void Main(string[] args) {
			Top t = new Top();
			ThreadStart ts= new ThreadStart(t.sayHello);
			Thread thread = new Thread(ts);
			thread.Start();
			Console.WriteLine("Thread " + Thread.CurrentThread.GetHashCode() + "Main terminated");
		}
	}
}