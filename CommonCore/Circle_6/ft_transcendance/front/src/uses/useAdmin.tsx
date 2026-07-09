import { useMemo, useState, useEffect } from "react";
import { useToastContext } from "../context/ToastContext";
import { useTranslation } from "react-i18next";

export interface User {
  id: string;
  registerDate: string;
  email: string;
  name: string;
  lastname: string;
  role: string;
}

export type SortConfig = {
  key: keyof User;
  direction: "asc" | "desc";
} | null;

const searchFields = [
  { key: "registerDate", label: "Register" },
  { key: "name", label: "Name" },
  { key: "lastname", label: "Last Name" },
  { key: "email", label: "E-mail" },
  { key: "role", label: "Role" },
] as const;

export const useAdmin = () => {
  const { addToast } = useToastContext();
  const { t } = useTranslation();

  const [users, setUsers] = useState<User[]>([]);
  const [isLoadingUsers, setIsLoadingUsers] = useState(true);
  const [searchValues, setSearchValues] = useState<Record<keyof User, string>>(
    searchFields.reduce(
      (acc, field) => ({ ...acc, [field.key]: "" }),
      {} as Record<keyof User, string>,
    ),
  );

  // Advanced Search states
  const [sortConfig, setSortConfig] = useState<SortConfig>(null);
  const [currentPage, setCurrentPage] = useState(1);
  const itemsPerPage = 5;

  useEffect(() => {
    const fetchUsers = async () => {
      try {
        const response = await fetch("/api/users", {
          method: "GET",
          credentials: "include",
        });
        if (response.ok) {
          const data = await response.json();
          setUsers(data.users ?? data);
        } else {
          addToast(t("Failed to fetch users."), "error");
        }
      } catch {
        addToast(t("Failed to fetch users."), "error");
      } finally {
        setIsLoadingUsers(false);
      }
    };
    fetchUsers();
  }, [addToast, t]);

  const filteredAndSortedUsers = useMemo(() => {
    const result = users.filter((user) => {
      return Object.entries(searchValues).every(([key, value]) => {
        if (!value) return true;
        const userValue = user[key as keyof User];
        if (typeof userValue === "string") {
          return userValue.toLowerCase().includes(value.toLowerCase());
        }
        return false;
      });
    });

    if (sortConfig !== null) {
      result.sort((a, b) => {
        if (a[sortConfig.key] < b[sortConfig.key]) {
          return sortConfig.direction === "asc" ? -1 : 1;
        }
        if (a[sortConfig.key] > b[sortConfig.key]) {
          return sortConfig.direction === "asc" ? 1 : -1;
        }
        return 0;
      });
    } else {
      // default sort
      result.sort((a, b) => a.lastname.localeCompare(b.lastname));
    }
    return result;
  }, [searchValues, users, sortConfig]);

  // Pagination logic
  const totalPages = Math.ceil(filteredAndSortedUsers.length / itemsPerPage);
  const paginatedUsers = useMemo(() => {
    const startIndex = (currentPage - 1) * itemsPerPage;
    return filteredAndSortedUsers.slice(startIndex, startIndex + itemsPerPage);
  }, [filteredAndSortedUsers, currentPage]);

  const requestSort = (key: keyof User) => {
    let direction: "asc" | "desc" = "asc";
    if (sortConfig && sortConfig.key === key && sortConfig.direction === "asc") {
      direction = "desc";
    }
    setSortConfig({ key, direction });
  };

  const handleInputChange = (fieldKey: keyof User, value: string) => {
    setSearchValues((prev) => ({ ...prev, [fieldKey]: value }));
    setCurrentPage(1);
  };

  const handleDeleteUser = async (userId: string): Promise<boolean> => {
    try {
      const response = await fetch(`/api/users/${userId}`, {
        method: "DELETE",
        credentials: "include",
      });
      if (response.ok) {
        setUsers(users.filter((user) => user.id !== userId));
        if (paginatedUsers.length === 1 && currentPage > 1) {
          setCurrentPage(currentPage - 1);
        }
        addToast(t("User deleted successfully."), "success");
        return true;
      } else {
        const data = await response.json().catch(() => ({}));
        addToast(data.error || t("Failed to delete user."), "error");
        return false;
      }
    } catch {
      addToast(t("Network error while deleting user."), "error");
      return false;
    }
  };

  const handleRoleChange = async (userId: string, newRole: string) => {
    try {
      const userToUpdate = users.find((u) => u.id === userId);
      if (!userToUpdate) return;

      const response = await fetch(`/api/users/${userId}`, {
        method: "PUT",
        headers: { "Content-Type": "application/json" },
        credentials: "include",
        body: JSON.stringify({
          email: userToUpdate.email,
          name: userToUpdate.name,
          lastname: userToUpdate.lastname,
          role: newRole,
        }),
      });
      if (response.ok) {
        setUsers(users.map((u) => (u.id === userId ? { ...u, role: newRole } : u)));
        addToast(t("User role updated successfully."), "success");
      } else {
        const data = await response.json().catch(() => ({}));
        addToast(data.error || t("Failed to update role."), "error");
      }
    } catch {
      addToast(t("Network error while updating role."), "error");
    }
  };

  return {
    filteredUsers: paginatedUsers,
    isLoadingUsers,
    handleInputChange,
    handleDeleteUser,
    handleRoleChange,
    searchFields,
    searchValues,
    requestSort,
    sortConfig,
    currentPage,
    setCurrentPage,
    totalPages,
  };
};
