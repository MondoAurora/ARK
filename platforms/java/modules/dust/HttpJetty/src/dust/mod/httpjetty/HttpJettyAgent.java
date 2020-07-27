package dust.mod.httpjetty;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.ServerConnector;

import dust.mod.DustComponents;

public class HttpJettyAgent implements DustComponents, DustComponents.DustAgent {
    Server server = null;
    
    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        switch (action) {
        case INIT:
            if ( null == server ) {
                server = new Server();
            } else if ( server.isRunning() ) {
                server.stop();
            }
            
            ServerConnector http = new ServerConnector(server);
            http.setPort(8080);
            http.setDefaultProtocol("HTTP/1.1");
            server.addConnector(http);
            
            return DustResultType.ACCEPT_PASS;
        case RELEASE:
            if ( (null != server) && server.isRunning() ) {
                server.stop();
            }

            return DustResultType.ACCEPT_PASS;            
        default:
            return DustResultType.ACCEPT_PASS;   
        }
    }
}
