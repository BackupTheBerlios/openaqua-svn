package openaqua.base;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

import org.apache.log4j.Logger;
import java.util.concurrent.locks.ReentrantReadWriteLock;
import java.util.List;

/**
 * @TODO Is the setup with a seperated function "createCommand" and a implicit call in getCommand fine?
 * @author tukaram
 *
 */
final public class CFactoryCommands  {
	private HashMap<Integer, ICommand> m_commandMap = new HashMap<Integer, ICommand>();
	private static Logger logger = Logger.getRootLogger();
	private ReentrantReadWriteLock builderLock = new ReentrantReadWriteLock(true);
	private ReentrantReadWriteLock commandLock = new ReentrantReadWriteLock(true);
	private List<CCommandBuilder> builderList = new ArrayList<CCommandBuilder>();
	private static CFactoryCommands INSTANCE = new CFactoryCommands();

	private CFactoryCommands(){
		//add a default builder
		registerBuilder(new CCommandBuilder());

	}

	final public static CFactoryCommands getInstance() {
		return INSTANCE;
	}


	final public void registerBuilder(final CCommandBuilder builder) {
		builderLock.writeLock().lock();
		try {
			builderList.add(builder);			
		}finally{
			builderLock.writeLock().unlock();
		}
	}

	final public void unregisterBuilder(final CCommandBuilder builder) {
		builderLock.writeLock().lock();
		try {
			builderList.remove(builder);			
		}finally{
			builderLock.writeLock().unlock();
		}
	}


	/**
	 * @param id
	 */
	final public ICommand getCommand(int id) {
		logger.debug("called CFactoryCommand for command id=" + id);
		ICommand result = null;

		//try to get the command
		commandLock.readLock().lock();
		try {
			result = m_commandMap.get(id);
		} finally {
			commandLock.readLock().unlock();
		}

		//if no result->try to create the command
		if (result == null) {
			ICommand cmd = createCommand(id);
			if (cmd != null) {
				commandLock.writeLock().lock();
				try {
					result = m_commandMap.get(id);
					if (result == null) {
						m_commandMap.put(id, cmd);
						result = cmd;
					}
				} finally {
					commandLock.writeLock().unlock();
				}
			}
		}

		//return whatever we have
		return result;
	}

	/**
	 * create a command. 
	 * 
	 * The method creates a new command instance. The new instance might be 
	 * used a  flyweight object in this factory or as a free usable object.<p>
	 * 

	 * While overwriting this method don't make assumtion about the used environment.
	 * Just create a commands. The code might look like <p>
	 * 
	 * <code>
	 * public ICommand createCommand(Integer id) { <br>		 
	 * 	if (id == 2000) {return new CommandFoo();}<br>
	 *  if (id == 2001) {return new CommandBar();}<br>
	 *  if (id == 2002) {<br>
	 *  	CMacro m(); <br>
	 *  	m.addCommand(new CommandFoo());<br>
	 *  	m.addCommand(new CommandBar());<br>
	 *  	return m;<br>
	 * }<br>
	 * </code><p>
	 * 
	 * 
	 * This method should be overwritten to create project specific commands
	 * The range between 0..1024 is reservered for future use and should not 
	 * be used for project specific commands.
	 * 
	 * @param id
	 * @return
	 */
	final public ICommand createCommand(Integer id) {

		ICommand result = null;
		builderLock.readLock().lock();

		try {
			Iterator it  = builderList.iterator();
			while(it.hasNext()) {
				Object o = it.next();
				if (o instanceof CCommandBuilder){
					CCommandBuilder builder = (CCommandBuilder) o;
					result = builder.createCommand(id);
					if (result != null) break;				
				}
			}

		} finally {
			builderLock.readLock().unlock();
		}
		return result;
	}


	/**
	 * 
	 * @param id
	 * @param c
	 */
	final public void addCommand(Integer id, ICommand c) {
		commandLock.writeLock().lock();
		try {
			m_commandMap.put(id, c);
		} finally {
			commandLock.writeLock().unlock();
		}
	}
}
