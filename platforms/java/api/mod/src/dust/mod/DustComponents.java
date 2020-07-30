package dust.mod;

public interface DustComponents {
    enum DustResultType {
        NOTIMPLEMENTED, REJECT, ACCEPT_PASS, ACCEPT, ACCEPT_READ, READ
    };

    enum DustAgentAction {
        INIT, BEGIN, PROCESS, END, RELEASE
    };

    enum DustEventLevel {
        CRITICAL, ERROR, WARNING, INFO, TRACE, DEBUG
    };

    enum DustDialogCmd {
        CHK, GET, SET, ADD, DEL
    };

	final long KEY_APPEND = -1;
	
	class DustToken {
        public final int store;
        public final int id;
        
        protected Integer entity = null;
	    
	    public DustToken(int store, int id) {
	        this.store = store;
	        this.id = id;
	    }
	    
	    public int getEntity() {
	        if ( null == entity ) {
	            entity = Dust.getTokenEntity(this);
	        }
	        
	        return entity;
	    }
    }
	
    public interface DustTokenResolver {
        int getTokenEntity(DustToken token);
    }


    class DustDialogTray {
		public Integer entity;
		public Integer token;
		public Integer key;

		public Object value;
		
		public void setToken(DustToken t) {
		    this.token = t.getEntity();
		}
	}

    public interface DustAgent {
        DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception;
    }

	public interface DustDialogAPI {
		<RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray);
		DustResultType visit(DustAgent visitor, DustDialogTray tray) throws Exception;
	}
	
	public class DustException extends RuntimeException {
		private static final long serialVersionUID = 1L;
		
		DustException(Throwable src) {
			super(src);
		}
		
		public static <FakeRet> FakeRet throwException(Throwable src, Object... params) {
			DustException e = ( src instanceof DustException ) ? (DustException ) src : new DustException(src);
			throw e;
		}
	}
}
