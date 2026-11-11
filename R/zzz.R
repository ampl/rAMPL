loadModule("rampl", TRUE)
loadModule("renvironment", TRUE)

loadModule("rvar_entity", TRUE)
loadModule("rvar_instance", TRUE)

loadModule("robj_entity", TRUE)
loadModule("robj_instance", TRUE)

loadModule("rcon_entity", TRUE)
loadModule("rcon_instance", TRUE)

loadModule("rset_entity", TRUE)
loadModule("rset_instance", TRUE)

loadModule("rparam_entity", TRUE)

# Where rAMPL is running: colab, kaggle, jupyter, rstudio, r, or rscript
.ampl_api_env <- function() {
  if (Sys.getenv("COLAB_RELEASE_TAG") != "") return("colab")
  if (Sys.getenv("KAGGLE_KERNEL_RUN_TYPE") != "") return("kaggle")
  if ("IRkernel" %in% loadedNamespaces()) return("jupyter")
  if (Sys.getenv("RSTUDIO") == "1") return("rstudio")
  if (interactive()) return("r")
  "rscript"
}

# Read by amplkey (inherited by AMPL and amplkey)
.onLoad <- function(libname, pkgname) {
  Sys.setenv(
    AMPL_API = "rAMPL",
    AMPL_API_VERSION = getNamespaceVersion(pkgname),
    AMPL_API_ENV = .ampl_api_env()
  )
}
