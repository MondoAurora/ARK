package dust.mod;

import dust.gen.DustGenConsts;

public interface DustComponents extends DustGenConsts {

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
        int getTokenMember(DustToken token);
    }
}
