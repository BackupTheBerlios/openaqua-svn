package de.tmobile.cabu.db4o;


import java.util.Random;
import com.db4o.ObjectContainer;

/**
 * @author behrenan
 *
 */
public class Db4oGenerator extends Thread{

	private int done = 0;
	private int maxContracts = Configuration.getInstance().getMaxContracts();
	private Random random = new Random();
	private ObjectContainer database;
	private boolean readTest;
	private ContractContainer contractContainer ;



	public Db4oGenerator(String threadName, ObjectContainer database, boolean readTest)  {
		super(threadName); 
		this.database = database;
		this.readTest = readTest;
		contractContainer = ContractContainerFactory.getInstance().getContractContainer(this.database);
	}

	public void setupDatabase() {
		System.out.println("Create Contract ?");

		for (int i = 0; i < Configuration.getInstance().getMaxContracts(); i++) {
			//System.out.println("Create Contract " + i);
			Contract c = new Contract(i);
			c.setValue(0);
			contractContainer.addContract(c);
			if ((i % 100000) == 0) {
				System.out.println("created " + i + " Contracts");
				database.commit();
			}
		}
		//contractContainer.saveContainer();		
		database.commit();


		System.out.println("created " +Configuration.getInstance().getMaxContracts()+ " Contracts");

	}

	public void ListAllContracts() {
		contractContainer.printContractList();
	}


	private void executeRead() {
		//random contractID
		int contractID = Math.abs(random.nextInt()) % Configuration.getInstance().getMaxContracts();
		
		//get contract
		Contract f = contractContainer.getContract(contractID);
		
		//check result
		if (f != null) {
			if (f.getContractKey().getKey() != contractID) {
				System.err.println("Error: Found Contract: " + f.getContractKey().getKey() + " looked for " + contractID);
			}
			//System.out.println("Found Contract: " + f.getContractKey().getKey());
		} else {
			System.err.println("Error: Didn't found Contract: " + contractID);
		}
		
		Stats.getInstance().addReadResults(1);
		//yield();
	}

	private void executeWrite() {
		//random contractID
		int contractID = Math.abs(random.nextInt()) % Configuration.getInstance().getMaxContracts();
		
		//get contract
		Contract f = contractContainer.getContract(new ContractKey(contractID));
		
		//check result
		if (f != null) {
			if (f.getContractKey().getKey() != contractID) {
				System.err.println("Error: Found Contract: " + f.getContractKey().getKey() + " looked for " + contractID);
			} else {
				System.out.println("Found Contract: " + f.getContractKey().getKey() + " with value: " + f.getValue());
				f.setValue(f.getValue()+1);
				contractContainer.updateContract(f);
				database.commit();
			}
		} else {
			System.err.println("Error: Didn't found Contract: " + contractID);
		}
		
		Stats.getInstance().addWriteResults(1);
		//yield();
	}


	/**
	 * The thread execution method
	 */
	public void run () {
		int loop = 0;
		for (int i = 0; i < Configuration.getInstance().getReqLoops(); i++){
			done = 0;
			while (done < maxContracts) {
				if (readTest == true) {
					executeRead();
				} else {
					executeWrite();
				}
				loop++;
				done++;
			}
		}
	}
}
