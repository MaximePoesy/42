import orangeLogo from "../assets/orange.svg";

interface LogoProps {
  name?: string;
}

export function Logo({ name = "Confhirter" }: LogoProps) {
  return (
    <div className="flex items-center gap-3">
      <img src={orangeLogo} alt="" aria-hidden="true" className="h-10 w-10" />
      <span className="text-orange-100 text-xl font-bold tracking-wide">{name}</span>
    </div>
  );
}
