package org.libsdl.app;

import android.os.Bundle;
import android.content.res.AssetManager;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.File;
import java.io.FileOutputStream;

public class JFEActivity extends SDLActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        try {
            copyAssets("characters/KOF-Rugal",
                new File(getFilesDir(), "characters/KOF-Rugal"));
        } catch (Exception e) {
            android.util.Log.e("JFE", "Asset copy failed", e);
        }

        super.onCreate(savedInstanceState);
    }

    private void copyAssets(String assetPath, File output)
            throws Exception {

        AssetManager manager = getAssets();
        String[] files = manager.list(assetPath);

        if (files == null || files.length == 0) {
            copyFile(assetPath, output);
            return;
        }

        if (!output.exists()) output.mkdirs();

        for (String name : files) {
            String child = assetPath + "/" + name;
            File target = new File(output, name);

            String[] nested = manager.list(child);

            if (nested != null && nested.length > 0) {
                copyAssets(child, target);
            } else {
                copyFile(child, target);
            }
        }
    }

    private void copyFile(String assetPath, File output)
            throws Exception {

        try (InputStream in = getAssets().open(assetPath);
             OutputStream out = new FileOutputStream(output)) {

            byte[] buffer = new byte[8192];
            int count;

            while ((count = in.read(buffer)) != -1) {
                out.write(buffer, 0, count);
            }
        }
    }
}
