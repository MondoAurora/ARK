package dust.app;

import java.io.File;
import java.lang.reflect.Method;
import java.net.URI;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import dust.mod.DustComponents;
import dust.mod.DustUtils;

public class DustApp implements DustAppComponents, DustComponents.DustAgent, DustAppComponents.NativeApp {

    URL toUrl(File root, String name) throws Exception {
        File f = new File(root, name);

        if (!f.exists()) {
            String ap = f.getAbsolutePath();
            DustException.throwException(null, "Missing library", ap);
        }

        URI uri = f.toURI();
        URL url = uri.toURL();

        return url;
    }

    class Module implements NativeModule {
        String modName;
        URLClassLoader modLoader;
        DustAgent modAgent;

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

                Class<?> c  = modLoader.loadClass("dust.mod.ModuleAgent");
                modAgent =(null == c) ? null :  (DustAgent) c.newInstance();
            } catch (Exception e) {
                DustException.throwException(e, modName, currLib);
            }
        }

        @Override
        public Object createNative(int type) {
            try {
                return classes.get(type).newInstance();
            } catch (Exception e) {
                return DustException.throwException(e, type);
            }
        }

        @Override
        public void assignClass(int type, String cName) {
            try {
                classes.put(type, modLoader.loadClass(cName));
            } catch (Exception e) {
                DustException.throwException(e, type, cName);
            }
        }
    }

    private final File modRoot;
    private final File extRoot;

    private Map<ClassLoader, Module> modules = new HashMap<>();
    private Map<Integer, Module> modByType = new HashMap<>();

    public DustApp(String runtimeModName, int[] storeRelay, String... libNames) {
        String ar = System.getenv("ARK_ROOT");

        File f = new File(ar, "platforms/java/lib");

        this.modRoot = new File(f, "mod");
        this.extRoot = new File(f, "ext");

        Module m = addModule(runtimeModName, storeRelay, libNames);
        
        try {
            Class<?> c  = m.modLoader.loadClass("dust.mod.Bootloader");
            Method method = c.getMethod("bootRuntime", NativeApp.class);
            method.invoke(null, this);
        } catch (Exception e) {
            DustException.throwException(e, "Calling createRuntime", runtimeModName);
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
        Module m = new Module(modName, storeRelay, libNames);

        modules.put(m.modLoader, m);

        return m;
    }

    @Override
    public int getSystemStoreIdx(DustToken token) {
        ClassLoader cl = token.getClass().getClassLoader();
        Module m = modules.get(cl);
        
        if ( null == m ) {
            DustUtils.log(DustEventLevel.TRACE, "Resolving token index from App");
            return token.store;
        } else {
            System.out.println("Loading token from module " + m.modName);
            return m.storeRelay[token.store];
        }
    }

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        return DustResultType.ACCEPT;
    }
}
