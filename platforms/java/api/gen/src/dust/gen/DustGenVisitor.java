package dust.gen;

import java.util.ArrayList;
import java.util.Stack;

public class DustGenVisitor<EventCtxType> implements DustGenConsts, DustGenConsts.DustGenCtxAgent<EventCtxType> {
    class RelayInfo {
        int start;
        DustGenAgent parent;
        boolean shareCtx;
        
        RelayInfo(boolean shareCtx) {
            this.shareCtx = shareCtx;
            this.start = depth;
            this.parent = current;
        }
    }
    
    int depth;
    
    DustGenAgent current;
    ArrayList<Object> procCtx;
    Stack<RelayInfo> relayStack;
    
    EventCtxType eventCtx;
    
    public DustGenVisitor(EventCtxType eventCtx, DustGenAgent root) {
        this.current = root;
        this.eventCtx = eventCtx;
    }
    
    @Override
    public EventCtxType getEventCtx() {
		return eventCtx;
	}
    
    @Override
    public void setEventCtx(EventCtxType ctx) {
    	this.eventCtx = ctx;
    }
    
    public Object getProcCtx() {
        return getProcCtx(null);
    }
    
    public Object getProcCtx(DustCreator<?> creator) {
        Object ret = ((null != procCtx) && (procCtx.size() > depth)) ? procCtx.get(depth) : null;
        
        if ( (null != creator) && (null == ret) ) {
            ret = creator.create();
            setProcCtx(ret);
        }
        
        return ret;
    }
    
    public void setProcCtx(Object ob) {
        if ( null == procCtx  ) {
            procCtx = new ArrayList<>();
        }
        
        for ( int i = procCtx.size(); i <= depth; ++i ) {
            procCtx.add(null);
        }
        
        procCtx.set(depth, ob);
    }
    
    public Object getProcCtxNeighbor(boolean up) {
        Object ret = null;
        
        if ( null != procCtx ) {
            int d = up ? depth - 1 : depth + 1;
            if ( (0 <= d) && (d < procCtx.size()) ) {
                ret = procCtx.get(d);
            }
        }
        
        return ret;
    }
    
    public DustResultType setRelay(DustGenAgent agent, boolean shareCtx) throws Exception {
        if ( null == relayStack ) {
            relayStack = new Stack<>();
        }
        
        relayStack.push(new RelayInfo(shareCtx));
        
        current = agent;
        
        if ( shareCtx ) {
            return null;
        } else {
            move(true);
            return agent.agentAction(DustAgentAction.BEGIN);
        }
    }
    
    private void move(boolean down) throws Exception {
        if ( down ) {
            ++ depth;
        } else {
            if ( null != relayStack ) {
                Exception e = null;
                
                while ( !relayStack.isEmpty() && (depth == relayStack.peek().start) ) {
                    RelayInfo ri = relayStack.pop();
                    if ( !ri.shareCtx ) {
                        try {
                            current.agentAction(DustAgentAction.END);
                        } catch ( Exception ex ) {
                            if ( null == e ) {
                                e = ex;
                            }
                        } finally {
                        	--depth;
                        }
                    }
                    current = ri.parent;
                    
                    try {
                        current.agentAction(DustAgentAction.END);
                    } catch ( Exception ex ) {
                        if ( null == e ) {
                            e = ex;
                        }
                    }

                }
                
                if ( null != e ) {
                    throw e;
                }
            }
            
            --depth;
        }
    }

    @Override
    public DustResultType agentAction(DustAgentAction action) throws Exception {
        switch (action) {
        case INIT:
            depth = 0;
            break;
        case RELEASE:
            if ( null != procCtx ) {
                procCtx.clear();
            }
            if ( 0 != depth ) {
                DustException.throwException(null, "invalid depth");
            }
            break;
        default:
            break;
        }
        
        try {
            if ( action == DustAgentAction.BEGIN ) {
                move(true);
            }
            return current.agentAction(action);
        } finally {
            if ( action == DustAgentAction.END ) {
                move(false);
            }
        }
    }
}
