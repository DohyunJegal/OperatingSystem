public class Consumer extends Thread {
    private Buffer sharedLocation;

    public Consumer(Buffer shared) {
        super("소비자");
        sharedLocation= shared;
    }

    public void run() {
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