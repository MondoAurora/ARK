package dust.gen;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipException;
import java.util.zip.ZipFile;

import dust.gen.DustGenConsts.DustEventLevel;

public class DustGenZipper {
    private static final int BUFFER = 32768;
    private static final String FNAME_EXT = ".zip";

    private static FilenameFilter FF_ZIP = new FilenameFilter() {
        @Override
        public boolean accept(File dir, String name) {
            return name.endsWith(FNAME_EXT);
        }
    };

    public static boolean update(File file) throws ZipException, IOException {
        boolean ret = false;

        if (file.exists()) {
            if (file.isDirectory()) {
                for (File f : file.listFiles(FF_ZIP)) {
                    ret |= update(f);
                }
            } else {
                File parent = file.getParentFile();
                String name = file.getName();

                if (FF_ZIP.accept(parent, name)) {
                    String resName = name.substring(0, name.lastIndexOf("."));
                    File target = new File(parent, resName);

                    if (target.exists()) {
                        long lm = target.lastModified();
                        if (target.exists() && (lm > file.lastModified())) {
                            return false;
                        } else {
                            target.renameTo(new File(parent, resName + "_" + DustGenUtils.strTimestamp(lm)));
                        }
                    }

                    ret = doUnzip(parent, file, resName);
                }
            }
        }
        return ret;
    }

    /**
     * Used source:
     * https://www.journaldev.com/960/java-unzip-file-example#comment-50097
     */

    private static boolean doUnzip(File destDir, File file, String resName) throws ZipException, IOException {
        String cPathRoot = destDir.getCanonicalPath();
        boolean first = true;

        try (ZipFile zipFile = new ZipFile(file)) {
            DustGenLog.log(DustEventLevel.INFO, "Unzipping file", file, file.length(), "bytes...");

            Enumeration<? extends ZipEntry> zipEntries = zipFile.entries();

            while (zipEntries.hasMoreElements()) {
                ZipEntry zipEntry = zipEntries.nextElement();
                String zipName = zipEntry.getName();

                if (first) {
                    if (!zipName.startsWith(resName)) {
                        destDir = new File(destDir, resName);
                        destDir.mkdirs();
                    }
                    first = false;
                }

                File newFile = new File(destDir, zipName);
                String cPathNew = newFile.getCanonicalPath();
                if (!cPathNew.startsWith(cPathRoot + File.separator)) {
                    DustGenException.throwException(null, "Zip entry:", cPathNew, "is outside of the target dir:" + cPathRoot);
                }

                if (zipEntry.isDirectory()) {
                    newFile.mkdirs();
                } else {
//                    long done = 0;
//                    StringBuilder doneStr = new StringBuilder();
//                    
//                    DevMonitor monitor = new DevMonitor(5000) {
//                        public void log() {
//                            DustGenLog.log(DustEventLevel.TRACE, doneStr, "bytes");
//                        };
//                    };
                    DustGenLog.log(DustEventLevel.INFO, "Extracting file", zipName, zipEntry.getSize(), "bytes...");

                    try (BufferedInputStream inputStream = new BufferedInputStream(zipFile.getInputStream(zipEntry))) {
                        try (FileOutputStream outputStream = new FileOutputStream(newFile)) {
                            
                            int count;
                            byte data[] = new byte[BUFFER];
                            
                            while ((count = inputStream.read(data, 0, BUFFER)) != -1) {
                                outputStream.write(data, 0, count);
//                                done += count;
//                                doneStr.replace(0, doneStr.length(), String.valueOf(done));
//                                if ( monitor.step() ) {
//                                    outputStream.flush();
//                                }
                            }
                        }
                    }
                }
            }
        }
        
        return !first;
    }
}
