package dust.mod.httpjetty;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.ServerConnector;

import dust.mod.DustComponents;

public class HttpJettyAgent extends DustComponents.DustAgentDefault implements DustComponents {
    Server server = null;

    @Override
    public DustResultType agentInit() throws Exception {
        if ( null == server ) {
            server = new Server();
        } else if ( server.isRunning() ) {
            server.stop();
        }
        
        ServerConnector http = new ServerConnector(server);
        http.setPort(8080);
        http.setDefaultProtocol("HTTP/1.1");
        server.addConnector(http);

        return super.agentInit();
    }
    
    @Override
    public DustResultType agentRelease() throws Exception {
        if ( (null != server) && server.isRunning() ) {
            server.stop();
        }
        
        return super.agentRelease();
    }
}
