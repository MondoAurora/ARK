package dust.app;

import java.io.File;
import java.lang.reflect.Method;
import java.net.URI;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import dust.mod.Dust;
import dust.mod.DustComponents;
import dust.mod.DustComponents.DustDialogAPI;

public class DustApp implements DustAppComponents, DustComponents.DustAgent, DustAppComponents.NativeApp {

    URL toUrl(File root, String name) throws Exception {
        File f = new File(root, name);

        boolean fe = f.exists();
        String ap = f.getAbsolutePath();

        URI uri = f.toURI();
        URL url = uri.toURL();

        return url;
    }

    class Module implements NativeModule {
        URLClassLoader modLoader;
        private Map<Integer, Class<?>> classes = new HashMap<>();

        public Module(String modName, String... libNames) {
            String currLib = null;

            try {
                ArrayList<URL> urls = new ArrayList<>();

                urls.add(toUrl(modRoot, modName));
                for (String ln : libNames) {
                    currLib = ln;
                    urls.add(toUrl(extRoot, currLib));
                }

                URL[] uu = new URL[urls.size()];
                uu = urls.toArray(uu);
                modLoader = new URLClassLoader(uu);
            } catch (Exception e) {
                DustException.throwException(e, currLib);
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

    private Set<Module> modules = new HashSet<Module>();
    private Map<Integer, Module> modByType = new HashMap<Integer, Module>();

    public DustApp(String runtimeModName, String... libNames) {
        String ar = System.getenv("ARK_ROOT");

        File f = new File(ar, "platforms/java/lib");
        boolean fe = f.exists();

        this.modRoot = new File(f, "mod");
        this.extRoot = new File(f, "ext");

        fe = this.modRoot.exists();
        fe = this.extRoot.exists();

        Module m = addModule(runtimeModName, libNames);

        try {
            Class<?> c;
            Method method;

            c = m.modLoader.loadClass("dust.mod.runtime.RuntimeAgent");
            method = c.getMethod("createRuntime", NativeApp.class);
            DustDialogAPI dlg = (DustDialogAPI) method.invoke(null, this);

            Dust.init(dlg);
        } catch (Exception e) {
            DustException.throwException(e, "DustApp", runtimeModName);
        }
    }

    @SuppressWarnings("unchecked")
    @Override
    public synchronized <RetType> RetType createNative(int type) {
        Module m = modByType.get(type);

        if (null == m) {
            for (Module tm : modules) {
                if (tm.classes.containsKey(type)) {
                    m = tm;
                    break;
                }
            }
        }

        return (RetType) m.createNative(type);
    }

    @Override
    public Module addModule(String modName, String... libNames) {
        Module m = new Module(modName, libNames);

        modules.add(m);

        return m;
    }

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        return DustResultType.ACCEPT;
    }
}
