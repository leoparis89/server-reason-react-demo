import Esbuild from "esbuild";
import Path from "path";

async function build(entryPoints, { env, output, nodePath }) {
  const outdir = output;
  const isDev = env === "development";

  try {
    await Esbuild.build({
      entryPoints,
      entryNames: "[name]",
      bundle: true,
      logLevel: "info",
      platform: "browser",
      format: "esm",
      splitting: true,
      outdir,
      nodePaths: nodePath ? [nodePath] : [],
      write: true,
      treeShaking: !isDev,
      minify: !isDev,
      define: {
        "process.env.NODE_ENV": `"${env}"`,
      },
    });

    entryPoints.forEach((ep) => {
      console.log(`Build completed: ${ep}`);
    });
  } catch (error) {
    console.error("Build failed:", error);
    process.exit(1);
  }
}

function parseArgv(argv) {
  const args = argv.slice(2);
  const result = { _: [] };

  for (let i = 0; i < args.length; i++) {
    const arg = args[i];
    if (arg.startsWith("--") && arg.includes("=")) {
      const [key, value] = arg.slice(2).split("=");
      result[key] = value;
    } else if (arg.startsWith("--")) {
      result[arg.slice(2)] = args[++i];
    } else {
      result._.push(arg);
    }
  }

  return result;
}

const flags = parseArgv(process.argv);
build(flags._, { env: flags.env || "development", output: flags.output || ".", nodePath: flags["node-path"] });
