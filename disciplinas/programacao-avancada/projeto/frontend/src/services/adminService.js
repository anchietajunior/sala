import { request } from "./api";

// As quantidades de Users e de Books do sistema: GET /api/admin/stats, só para o Admin
export function getStats() {
  return request("/api/admin/stats");
}
