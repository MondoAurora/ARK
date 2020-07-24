package dust.mod;

public interface DustComponents {
	enum DustResultType {
		NOTIMPLEMENTED, REJECT, ACCEPT_PASS, ACCEPT, ACCEPT_READ, READ
	};

	public interface DustAgent {
		DustResultType agentInit() throws Exception;

		DustResultType agentBegin() throws Exception;

		DustResultType agentProcess() throws Exception;

		DustResultType agentEnd() throws Exception;

		DustResultType agentRelease() throws Exception;
	}

	public abstract class DustAgentDefault implements DustAgent {
		@Override
		public DustResultType agentInit() throws Exception {
			return DustResultType.ACCEPT_PASS;
		}

		@Override
		public DustResultType agentBegin() throws Exception {
			return DustResultType.ACCEPT_PASS;
		}

		@Override
		public DustResultType agentProcess() throws Exception {
			return DustResultType.ACCEPT_PASS;
		}

		@Override
		public DustResultType agentEnd() throws Exception {
			return DustResultType.ACCEPT_PASS;
		}

		@Override
		public DustResultType agentRelease() throws Exception {
			return DustResultType.ACCEPT_PASS;
		}
	}

	enum DustDialogCmd {
		CHK, GET, SET, ADD, DEL
	};

	final long KEY_APPEND = -1;

	class DustDialogTray {
		public DustDialogCmd cmd;
		
		public Long entity;
		public Long token;
		public Long key;

		public Object val;
	}

	public interface DustDialogAPI {
		<ValType> ValType access(DustDialogTray tray);
		DustResultType visit(Long entity, Long token, DustAgent visitor);
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
