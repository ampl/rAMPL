#!/bin/bash
BASEDIR=`dirname $0`
cd $BASEDIR
set -ex

SCRIPT=dependencies.tmp.R
trap 'rm -f $SCRIPT' EXIT
cat > $SCRIPT <<'RSCRIPT'
pkgs <- c("Rcpp", "testthat")
repos <- getOption("repos")
if (is.na(repos["CRAN"]) || repos["CRAN"] == "@CRAN@") repos["CRAN"] <- "https://cloud.r-project.org"
withCallingHandlers(
  install.packages(pkgs, repos = repos, INSTALL_opts = c("--no-multiarch")),
  warning = function(w) cat("::warning::", conditionMessage(w), "\n", sep = "")
)
missing <- pkgs[!vapply(pkgs, requireNamespace, logical(1), quietly = TRUE)]
if (length(missing) > 0) {
  cat("::error::Failed to install: ", paste(missing, collapse = ", "), "\n", sep = "")
  quit(status = 1)
}
RSCRIPT
R --no-save -q -f $SCRIPT
