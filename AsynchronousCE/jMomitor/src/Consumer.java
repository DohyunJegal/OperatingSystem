class Consumer extends Thread {
    Producer producer;

    Consumer(Producer p) {
        producer = p;
    }

    public void run() {	// Java의 쓰레드 생성을 위해 Thread를 상속받고 run() 생성
        try {
            while (true) {
                String message = producer.getMessage();
                System.out.println("Got message: " + message);
                sleep(200);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void main(String args[]) {
        Producer producer = new Producer();
        producer.start();
        new Consumer(producer).start();
    }
}