public class SharedBufferTest {	// 동기화를 하지않고 공유객체를 변경하는 쓰레드를 시작
    public static void main(String[] args) {
        Buffer sharedLocation = new UnsynchronizedBuffer();
		
        Producer producer = new Producer(sharedLocation);
        Consumer consumer = new Consumer(sharedLocation);

        producer.start();	// 생산자와 소비자 쓰레드를 시작
        consumer.start();
    }
}