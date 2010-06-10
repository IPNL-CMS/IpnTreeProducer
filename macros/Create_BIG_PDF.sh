#!/bin/bash
# Script to create THE BIG PDF with all plots
# Written by O. Bondu (June 2010)

CMSSW_release="CMSSW_3_5_8_patch3"

syntax="Syntax ${0} {directory}"

if [[ -z ${1} ]]
then
  echo ${syntax}
  exit 1
fi

directory=${1}

cd ${directory}

echo "
\documentclass{beamer}

\usepackage[english]{babel}
\usepackage{amsmath}
\usepackage{amsfonts}
\usepackage{amssymb}
\usepackage{graphicx}
\usepackage{colortbl}
\usepackage{wasysym}
\usepackage[abs]{overpic}
\usepackage{hyperref}

\setcounter{tocdepth}{1}

\title{SuperClusters DATA/MC comparisons}
\author{IPN Lyon group}
\institute{IPN Lyon}

\begin{document}


\begin{frame}
\titlepage
\end{frame}

" > presentation.tex

# ******************** SuperClusters
echo "\section{SuperClusters}" >> presentation.tex

for cut in `echo "isAfterCut3 isAfterCut3_RawEtGT2 isAfterCut3_RawEtGT4 isAfterCut3_RawEtGT10"`
do
echo "
\subsection{${cut}}
" >> presentation.tex
	for variable in `echo "E Et RawE RawEt Eta Phi etaWidth phiWidth"`
	do
		echo "
\subsubsection{${variable}}
\begin{frame}
\begin{center}
\includegraphics[width=.3\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EB.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EE.pdf}
\\
\includegraphics[width=.3\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_log.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EB_log.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EE_log.pdf}
\end{center}
\end{frame}
\begin{frame}
\begin{center}
\includegraphics[width=.3\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EE.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EEM.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EEP.pdf}
\\
\includegraphics[width=.3\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EE_log.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EEM_log.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EEP_log.pdf}
\end{center}
\end{frame}
" >> presentation.tex
	done
done

# ********************* Photons
echo "\section{Photons}" >> presentation.tex

for cut in `echo "isAfterCut7"`
do
echo "
\subsection{${cut}}
" >> presentation.tex
  for variable in `echo "E Et Eta Phi SCEnergy SCEt SCRawEnergy SCRawEt covIetaIeta covIphiIphi etaWidth phiWidth"`
  do
    echo "
\subsubsection{${variable}}
\begin{frame}
\begin{center}
\includegraphics[width=.3\textwidth]{pdf/DataMC_Photon_${variable}_${cut}.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EB.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EE.pdf}
\\
\includegraphics[width=.3\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_log.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EB_log.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EE_log.pdf}
\end{center}
\end{frame}
\begin{frame}
\begin{center}
\includegraphics[width=.3\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EE.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EEM.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EEP.pdf}
\\
\includegraphics[width=.3\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EE_log.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EEM_log.pdf}
\includegraphics[width=.3\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EEP_log.pdf}
\end{center}
\end{frame}
" >> presentation.tex
  done
done


echo "

\end{document}
" >> presentation.tex


echo "Creating the pdf with pdflatex"
pdflatex presentation.tex

pdflatex presentation.tex
pdflatex presentation.tex

exit 0
