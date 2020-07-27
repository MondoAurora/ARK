package dust.mod;

public interface DustComponents {
    enum DustResultType {
        NOTIMPLEMENTED, REJECT, ACCEPT_PASS, ACCEPT, ACCEPT_READ, READ
    };

    enum DustAgentAction {
        INIT, BEGIN, PROCESS, END, RELEASE
    };

	enum DustDialogCmd {
		CHK, GET, SET, ADD, DEL
	};

	final long KEY_APPEND = -1;

	class DustDialogTray {
		public Integer entity;
		public Integer token;
		public Integer key;

		public Object value;
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
