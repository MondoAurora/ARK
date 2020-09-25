package dust.gen;

public interface DustGenConsts {
    final long KEY_APPEND = -1;
    
    enum DustResultType {
        NOTIMPLEMENTED, REJECT, ACCEPT_PASS, ACCEPT, ACCEPT_READ, READ;
    };

    enum DustAgentAction {
        INIT, BEGIN, PROCESS, END, RELEASE
    };

    enum DustDialogCmd {
        CHK, GET, SET, ADD, DEL
    };
    
    enum DustValType {
        INT, REAL, REF, RAW
    }
    
    enum DustCollType {
        ONE, SET, ARR, MAP
    }

    enum DustEventLevel {
        CRITICAL, ERROR, WARNING, INFO, TRACE, DEBUG
    };

    public interface DustEntity {
    }
    
    enum EntityBlock {
        Entity, Member
    }
    
	class DustEntityDelta {
		public DustDialogCmd cmd;
		
		public DustEntity target;
		public Object eKey;

		public DustEntity member;
		public Object value;
		public Object key;
		
		public DustEntityDelta(DustDialogCmd cmd, DustEntity target, Object eKey, DustEntity member, Object value, Object key) {
			this.cmd = cmd;
			this.target = target;
			this.eKey = eKey;
			this.member = member;
			this.value = value;
			this.key = key;
		}
	}
    
    public class DustEntityContext {
    	public EntityBlock block;
    	
    	public DustEntity entity;
    	public Object eKey;
    	
    	public DustEntity member;
    	
    	public DustValType valType;
    	public DustCollType collType;
        
    	public Object value;
    	public Object mKey;
    	
    	public DustEntityContext() {
		}
    	
    	public DustEntityContext(DustEntityContext src) {
    		load(src);
		}
    	
		public void load(DustEntityContext src) {
			this.block = src.block;
			this.entity = src.entity;
			this.member = src.member;
			this.valType = src.valType;
			this.collType = src.collType;
			this.value = src.value;
			this.mKey = src.mKey;
			this.eKey = src.eKey;
		}
		
		public void reset() {
			this.block = null;
			this.entity = null;
			this.member = null;
			this.valType = null;
			this.collType = null;
			this.value = null;
			this.mKey = null;
			this.eKey = null;
		}
		
		@Override
		public String toString() {
			StringBuilder sb = DustGenUtils.sbAppend(null, ",", true, block, entity, eKey, member, valType, collType, value, mKey);
			return sb.toString();
		}
    }

    public interface DustGenAgent {
        DustResultType agentAction(DustAgentAction action) throws Exception;
    }

    public interface DustGenCtxAgent<EventCtxType> extends DustGenAgent {
    	void setEventCtx(EventCtxType ctx);
    	EventCtxType getEventCtx();
    }

    public class DustException extends RuntimeException {
        private static final long serialVersionUID = 1L;

        DustException(Throwable src) {
            super(src);
        }

        public static <FakeRet> FakeRet throwException(Throwable src, Object... params) {
            DustGenLog.log(DustEventLevel.CRITICAL, params);
            DustException e = (src instanceof DustException) ? (DustException) src : new DustException(src);
            throw e;
        }
    }

    public interface DustHasDefault<T> {
        T getDefault();
    }

    public interface DustCreator<T> {
        T create();
    }
}
