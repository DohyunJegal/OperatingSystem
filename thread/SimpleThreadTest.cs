using System;
using System.Threading;	// 쓰레드 사용을 위해 추가

namespace ConsoleApplication {
	public class Top {	
		private int limit = 0;
		public void sayHello() {
			while(limit < 10) {
				Thread th= Thread.CurrentThread;	// 쓰레드 지정
				Console.WriteLine("Thread " + th.GetHashCode() + ": " + limit++);
			}
		}
	}

	class SimpleThreadTest {
		static void Main(string[] args) {
			Top t = new Top();
			ThreadStart ts= new ThreadStart(t.sayHello);	// 쓰레드 생성
			Thread thread = new Thread(ts);
			thread.Start();	// 쓰레드 시작
			Console.WriteLine("Thread " + Thread.CurrentThread.GetHashCode() + "Main terminated");	// 현재 쓰레드의 해쉬코드를 가져옴
		}
	}
}