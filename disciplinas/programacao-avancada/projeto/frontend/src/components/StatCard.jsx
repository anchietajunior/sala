import Card from "./Card";

// Uma quantidade do Admin Dashboard: o rótulo e o número em destaque
export default function StatCard({ label, value }) {
  return (
    <Card>
      <p className="text-sm font-medium text-slate-500">{label}</p>
      <p className="mt-1 text-3xl font-bold text-slate-900">{value}</p>
    </Card>
  );
}
