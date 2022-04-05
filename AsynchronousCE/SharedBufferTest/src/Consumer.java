public class Consumer extends Thread { // 소비자 클래스
    private Buffer sharedLocation;

    public Consumer(Buffer shared) {
        super("소비자");
        sharedLocation= shared;
    }

    public void run() {	// Thread 클래스를 상속 후 run()을 정의하여 쓰레드 생성
        int sum = 0;

        for(int count = 1; count <= 4; count++) {


            try{
                Thread.sleep((int)(Math.random( )*3001));
                sum += sharedLocation.get( );
            }
            catch(InterruptedException exception) {
                exception.printStackTrace( );
            }
        }

        System.out.println(getName( ) + " 읽은값합계: " + sum);
        System.out.println("--> " + getName( ) + " 종료!");
    }
}