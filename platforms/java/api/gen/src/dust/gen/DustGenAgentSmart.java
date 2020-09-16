package dust.gen;

import java.util.ArrayList;
import java.util.Stack;

public class DustGenAgentSmart implements DustGenConsts, DustGenConsts.DustGenAgent {
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
    ArrayList<Object> ctx;
    Stack<RelayInfo> relayStack;
    
    public DustGenAgentSmart(DustGenAgent root) {
        this.current = root;
    }
    
    public Object getCtxOb() {
        return getCtxOb(null);
    }
    
    public Object getCtxOb(DustCreator<?> creator) {
        Object ret = ((null != ctx) && (ctx.size() > depth)) ? ctx.get(depth) : null;
        
        if ( (null != creator) && (null == ret) ) {
            ret = creator.create();
            setCtxOb(ret);
        }
        
        return ret;
    }
    
    public void setCtxOb(Object ob) {
        if ( null == ctx  ) {
            ctx = new ArrayList<>();
        }
        
        for ( int i = ctx.size(); i <= depth; ++i ) {
            ctx.add(null);
        }
        
        ctx.set(depth, ob);
    }
    
    public Object getCtxNeighbor(boolean up) {
        Object ret = null;
        
        if ( null != ctx ) {
            int d = up ? depth - 1 : depth + 1;
            if ( (0 <= d) && (d < ctx.size()) ) {
                ret = ctx.get(d);
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
            if ( null != ctx ) {
                ctx.clear();
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
