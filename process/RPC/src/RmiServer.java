import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.registry.*;

public class RmiServer extends UnicastRemoteObject implements RmiServerIntf{
    public static final String MESSAGE = "Hello World";
    public RmiServer( ) throws RemoteException{
        super(0);
    }

    public String getMessage( ) {
        return MESSAGE;
    }
    public static void main(String args[]) throws Exception {
        System.out.println("RMI server started");
        try{
            LocateRegistry.createRegistry(1099);
            System.out.println("java RMI registry created.");
        } catch(RemoteException e) {
            System.out.println("java RMI registry already exists.");
        }

        RmiServer obj= new RmiServer();

        Naming.rebind("//localhost/RmiServer", obj);
        System.out.println("PeerServerbound in registry");
    }
}