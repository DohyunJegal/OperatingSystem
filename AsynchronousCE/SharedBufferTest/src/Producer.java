public class Producer extends Thread {	// 생산자 클래스
    private Buffer sharedLocation;

    public Producer(Buffer shared) {
        super("생산자");
        sharedLocation = shared;
    }

    public void run() {	// Thread 클래스를 상속한 후 run()을 정의하여 쓰레드를 생성
        for (int count = 1; count <= 4; count++) {
            try {
                Thread.sleep((int) (Math.random() * 3001));
                sharedLocation.set(count);
            } catch (InterruptedException exception) {
                exception.printStackTrace();
            }
        }
        System.out.println("--> " + getName() + " 종료!");
    }
}
