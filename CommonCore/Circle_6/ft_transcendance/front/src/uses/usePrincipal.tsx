import { useState, useRef, useCallback } from "react";
import { useToastContext } from "../context/ToastContext";
import { useTranslation } from "react-i18next";

export type AiMode = "records" | "general";

export interface Prop {
  uploadFileName: string;
  convertFileName: string;
  downloadFileName: string;
  fileExtension: string;
  fileContent: string;
  setFileContent: React.Dispatch<React.SetStateAction<string>>;
  fileOutput: string;
  fileUploadRef: React.RefObject<HTMLInputElement | null>;
  fileConvertRef: React.RefObject<HTMLInputElement | null>;
  handleButtonClick: (ref: React.RefObject<HTMLInputElement | null>) => void;
  handleSelectedFile: (event: React.ChangeEvent<HTMLInputElement>) => void;
  handleConvertClick: () => void;
  isConverting: boolean;
  handleDownloadClick: () => void;
  setDownloadFileName: React.Dispatch<React.SetStateAction<string>>;
  setFileExtension: React.Dispatch<React.SetStateAction<string>>;
  aiMessage: string;
  setAiMessage: React.Dispatch<React.SetStateAction<string>>;
  aiResponse: string;
  isAiLoading: boolean;
  handleAiSend: () => void;
  aiMode: AiMode;
  setAiMode: React.Dispatch<React.SetStateAction<AiMode>>;
}

export const usePrincipal = (): Prop => {
  const { addToast } = useToastContext();
  const { t } = useTranslation();

  const [uploadFileName, setUploadFileName] = useState("");
  const [convertFileName, setConvertFileName] = useState("");
  const [downloadFileName, setDownloadFileName] = useState("");
  const [fileExtension, setFileExtension] = useState("");
  const [fileContent, setFileContent] = useState("");
  const [fileOutput, setFileOutput] = useState("");
  const [isConverting, setIsConverting] = useState(false);

  // AI State
  const [aiMessage, setAiMessage] = useState("");
  const [aiResponse, setAiResponse] = useState("");
  const [isAiLoading, setIsAiLoading] = useState(false);
  const [aiMode, setAiMode] = useState<AiMode>("records");

  const fileUploadRef = useRef<HTMLInputElement>(null);
  const fileConvertRef = useRef<HTMLInputElement>(null);

  const handleAiSend = useCallback(async () => {
    if (!aiMessage.trim()) return;
    setIsAiLoading(true);
    setAiResponse("");

    // Records mode hits the RAG pipeline (vector retrieval + grounded answer).
    // General mode hits the bare LLM (no record context, model's own knowledge).
    const endpoint = aiMode === "records" ? "/ai/rag/stream" : "/ai/llm/stream";

    try {
      const res = await fetch(endpoint, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ question: aiMessage }),
        credentials: "include",
      });

      if (res.status === 429) {
        const retry = res.headers.get("Retry-After") ?? "?";
        addToast(t("rate_limit_reached", { retry }), "error");
        return;
      }
      if (!res.ok || !res.body) throw new Error(`HTTP ${res.status}`);

      const reader = res.body.getReader();
      const decoder = new TextDecoder();
      let buffer = "";

      while (true) {
        const { done, value } = await reader.read();
        if (done) break;
        buffer += decoder.decode(value, { stream: true });

        const events = buffer.split("\n\n");
        buffer = events.pop() ?? "";

        for (const evt of events) {
          const lines = evt.split("\n");
          const eventType = lines.find((l) => l.startsWith("event: "))?.slice(7);
          const dataLine = lines.find((l) => l.startsWith("data: "))?.slice(6);
          if (!dataLine) continue;
          const data = JSON.parse(dataLine);

          if (eventType === "token") {
            setAiResponse((prev) => prev + data.content);
          } else if (eventType === "error") {
            addToast(t("ai_error", { message: data.message }), "error");
          }
        }
      }
      setAiMessage("");
    } catch {
      addToast(t("Network error with AI service."), "error");
    } finally {
      setIsAiLoading(false);
    }
  }, [aiMessage, aiMode, addToast, t]);

  const handleButtonClick = useCallback((ref: React.RefObject<HTMLInputElement | null>) => {
    if (ref.current) {
      ref.current.click();
    }
  }, []);

  const handleSelectedFile = useCallback((event: React.ChangeEvent<HTMLInputElement>) => {
    if (event.target.files && event.target.files.length > 0) {
      const file = event.target.files[0];
      setUploadFileName(file.name);
      setConvertFileName("");
      const reader = new FileReader();
      reader.onload = (e) => {
        if (e.target && typeof e.target.result === "string") {
          setFileContent(e.target.result);
        }
      };
      reader.readAsText(file);
    }
  }, []);

  const handleConvertClick = useCallback(async () => {
    if (!fileContent) {
      addToast(t("Please upload a file first."), "info");
      return;
    }

    setIsConverting(true);
    setConvertFileName(t("Converting..."));

    try {
      const response = await fetch("/ai/convert", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ hl7: fileContent }),
        credentials: "include",
      });

      const data = await response.json();
      if (response.ok) {
        setFileOutput(data.fhir);
        setConvertFileName(t("Converted!"));
        addToast(t("File converted successfully!"), "success");
      } else {
        setConvertFileName(t("Error"));
        addToast(data.error || t("Conversion failed."), "error");
      }
    } catch {
      setConvertFileName(t("Error"));
      addToast(t("Network error during conversion."), "error");
    } finally {
      setIsConverting(false);
    }
  }, [fileContent, addToast, t]);

  const handleDownloadClick = useCallback(() => {
    if (!fileOutput) {
      addToast(t("Nothing to download. Convert a file first."), "info");
      return;
    }

    const fileName = downloadFileName.trim() === "" ? "fhir-output" : downloadFileName;
    const extension = fileExtension.trim() === "" ? "json" : fileExtension;
    const blob = new Blob([fileOutput], { type: `application/${extension}` });
    const url = URL.createObjectURL(blob);

    try {
      const a = document.createElement("a");
      a.href = url;
      a.download = `${fileName}.${extension}`;
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
    } finally {
      URL.revokeObjectURL(url);
    }
  }, [fileOutput, downloadFileName, fileExtension, addToast, t]);

  return {
    uploadFileName,
    handleButtonClick,
    fileUploadRef,
    fileConvertRef,
    handleSelectedFile,
    convertFileName,
    handleConvertClick,
    isConverting,
    fileContent,
    setFileContent,
    fileOutput,
    downloadFileName,
    setDownloadFileName,
    fileExtension,
    setFileExtension,
    handleDownloadClick,
    aiMessage,
    setAiMessage,
    aiResponse,
    isAiLoading,
    aiMode,
    setAiMode,
    handleAiSend,
  };
};
