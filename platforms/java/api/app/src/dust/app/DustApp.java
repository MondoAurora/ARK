package dust.app;

import java.io.File;
import java.lang.reflect.Method;
import java.net.URI;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import dust.gen.DustGenException;
import dust.gen.DustGenLog;
import dust.mod.Dust;
import dust.mod.DustComponents;

public class DustApp implements DustAppComponents, DustComponents.DustAgent, DustAppComponents.NativeApp {

    URL toUrl(File root, String name) throws Exception {
        File f = new File(root, name);

        if (!f.exists()) {
            String ap = f.getAbsolutePath();
            DustGenException.throwException(null, "Missing library", ap);
        }

        URI uri = f.toURI();
        URL url = uri.toURL();

        return url;
    }

    class Module implements NativeModule {
        String modName;
        URLClassLoader modLoader;
        DustAgent modAgent;
        Integer modEntity = null;

        private Map<Integer, Class<?>> classes = new HashMap<>();

        int[] storeRelay;

        public Module(String modName, int[] storeRelay, String... libNames) {
            this.modName = modName;
            this.storeRelay = storeRelay;

            String currLib = null;

            try {
                ArrayList<URL> urls = new ArrayList<>();

                urls.add(toUrl(modRoot, modName + ".jar"));
                for (String ln : libNames) {
                    currLib = ln;
                    urls.add(toUrl(extRoot, currLib));
                }

                URL[] uu = new URL[urls.size()];
                uu = urls.toArray(uu);
                modLoader = new URLClassLoader(uu);

                Class<?> c = modLoader.loadClass("dust.mod." + modName);
                modAgent = (DustAgent) c.newInstance();
            } catch (Exception e) {
                DustGenException.throwException(e, modName, currLib);
            }
        }

        public void initModule(AppTokens appTokens) {
            DustDialogTray t = new DustDialogTray();

            t.setToken(appTokens.typeModule);
            modEntity = Dust.access(DustDialogCmd.ADD, t);

            t.entity = modEntity;
            t.token = null;
            int kTxt = appTokens.typeText.getEntity();
            int kNat = appTokens.refNative.getEntity();

            try {
                modAgent.agentAction(DustAgentAction.INIT, t);

                t.setToken(appTokens.refObjects);
                Dust.visit(new DustAgent() {
                    @Override
                    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
                        Integer natType = t.key;
                        
                        t.entity = (Integer) t.value;
                        t.token = kNat;
                        t.key = kTxt;
                        
                        String natClass = Dust.access(DustDialogCmd.GET, t);
                        
                        classes.put(natType, modLoader.loadClass(natClass));
                        return DustResultType.READ;
                    }
                }, t);
            } catch (Exception e) {
               DustGenException.throwException(e);
            }
        }

        @Override
        public Object createNative(int type) {
            try {
                return classes.get(type).newInstance();
            } catch (Exception e) {
                return DustGenException.throwException(e, type);
            }
        }
    }

    private final File modRoot;
    private final File extRoot;

    AppTokens appTokens;

    private Map<ClassLoader, Module> modules = new HashMap<>();
    private Map<Integer, Module> modByType = new HashMap<>();

    public DustApp(AppTokens appTokens, String runtimeModName, int[] storeRelay, String... libNames) {
        this.appTokens = appTokens;

        String ar = System.getenv("ARK_ROOT");

        File f = new File(ar, "platforms/java/lib");

        this.modRoot = new File(f, "mod");
        this.extRoot = new File(f, "ext");

        Module m = addModule(runtimeModName, storeRelay, libNames);

        try {
            Method method = m.modAgent.getClass().getMethod("bootRuntime", NativeApp.class);
            method.invoke(null, this);

            m.initModule(appTokens);
        } catch (Exception e) {
            DustGenException.throwException(e, "Calling createRuntime", runtimeModName);
        }

    }

    @SuppressWarnings("unchecked")
    @Override
    public synchronized <RetType> RetType createNative(int type) {
        Module m = modByType.get(type);

        if (null == m) {
            for (Module tm : modules.values()) {
                if (tm.classes.containsKey(type)) {
                    m = tm;
                    break;
                }
            }
        }

        return (RetType) m.createNative(type);
    }

    @Override
    public Module addModule(String modName, int[] storeRelay, String... libNames) {
        DustGenLog.log(DustEventLevel.TRACE, "Loading module", modName);
        
        Module m = new Module(modName, storeRelay, libNames);

        if (!modules.isEmpty()) {
            m.initModule(appTokens);
        }

        modules.put(m.modLoader, m);

        return m;
    }

    @Override
    public int getSystemStoreIdx(DustToken token) {
        ClassLoader cl = token.getClass().getClassLoader();
        Module m = modules.get(cl);

        if (null == m) {
//            DustUtils.log(DustEventLevel.TRACE, "Resolving token index from App");
            return token.store;
        } else {
//            System.out.println("Loading token from module " + m.modName);
            return m.storeRelay[token.store];
        }
    }

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        return DustResultType.ACCEPT;
    }
}
