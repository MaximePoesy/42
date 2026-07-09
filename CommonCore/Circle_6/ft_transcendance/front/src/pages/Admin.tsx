import { TrashButton } from "../components/Button";
import { useAdmin } from "../uses/useAdmin";
import type { User } from "../uses/useAdmin";
import { useTranslation } from "react-i18next";
import { ConfirmModal } from "../components/ConfirmModal";
import { useState, useRef } from "react";
import { useAuth } from "../context/AuthContext";
import { useNavigate } from "react-router-dom";
import { UserMenu } from "../components/UserMenu";
import { Logo } from "../components/Logo";

export default function Admin() {
  const { t } = useTranslation();
  const { logout } = useAuth();
  const navigate = useNavigate();

  const {
    filteredUsers,
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
  } = useAdmin();

  const [showDeleteConfirm, setShowDeleteConfirm] = useState(false);
  const [userToDelete, setUserToDelete] = useState<string | null>(null);
  const [isDeleting, setIsDeleting] = useState(false);

  const [showRoleConfirm, setShowRoleConfirm] = useState(false);
  const [pendingRoleChange, setPendingRoleChange] = useState<{
    userId: string;
    newRole: string;
  } | null>(null);

  const paginationStatusRef = useRef<HTMLSpanElement>(null);

  const handleConfirmDelete = async () => {
    if (!userToDelete) return;
    setIsDeleting(true);
    const success = await handleDeleteUser(userToDelete);
    setIsDeleting(false);
    if (success) {
      setShowDeleteConfirm(false);
      setUserToDelete(null);
    }
  };

  const handleConfirmRoleChange = async () => {
    if (!pendingRoleChange) return;
    await handleRoleChange(pendingRoleChange.userId, pendingRoleChange.newRole);
    setShowRoleConfirm(false);
    setPendingRoleChange(null);
  };

  const getSortAriaLabel = (key: keyof User) => {
    if (sortConfig?.key !== key) return "none" as const;
    return sortConfig.direction === "asc" ? ("ascending" as const) : ("descending" as const);
  };

  return (
    <main id="main-content" tabIndex={-1} className="min-h-screen p-3 md:p-5 bg-orange-950">
      <div className="flex items-center justify-between pt-4 pr-2 md:pr-5">
        <div className="hidden md:block w-40" />
        <div className="flex-1 flex justify-center">
          <Logo />
        </div>
        <div className="w-auto md:w-40 flex justify-end">
          <UserMenu showHomeLink={true} onGoToHome={() => navigate("/")} onLogout={logout} />
        </div>
      </div>
      <div className="flex flex-col flex-1 gap-5 p-3 md:p-5">
        <div
          role="search"
          aria-label={t("User search and filters")}
          className="flex flex-col md:flex-row gap-3 md:gap-5 p-4 md:p-5 items-center justify-center border-3 border-orange-800 rounded-lg"
        >
          <div className="flex flex-col md:flex-row flex-1 gap-3 md:gap-5 w-full">
            {searchFields.map((field) => (
              <div key={field.key} className="flex-1">
                <label className="sr-only" htmlFor={`search-${field.key}`}>
                  {t("Search")} {t(field.label)}
                </label>
                <input
                  id={`search-${field.key}`}
                  type="search"
                  className="w-full p-2 text-orange-200 bg-orange-800 rounded-lg focus:ring-2 focus:ring-orange-400 focus:outline-none"
                  placeholder={`${t("Search")} ${t(field.label)}`}
                  value={searchValues[field.key as keyof User]}
                  onChange={(e) => handleInputChange(field.key as keyof User, e.target.value)}
                />
              </div>
            ))}
          </div>
        </div>

        <section
          className="flex-1 flex-col flex gap-5 p-4 md:p-5 border-3 border-orange-800 rounded-lg overflow-hidden"
          aria-label={t("User Management List")}
        >
          <div className="flex-1 overflow-x-auto overflow-y-auto">
            {isLoadingUsers ? (
              <div
                className="flex justify-center items-center py-10"
                role="status"
                aria-label={t("Loading users...")}
              >
                <div
                  className="w-8 h-8 border-4 border-orange-400 border-t-orange-700 rounded-full animate-spin"
                  aria-hidden="true"
                />
              </div>
            ) : (
              <table className="w-full border-collapse min-w-150">
                <thead>
                  <tr className="bg-orange-900 rounded-lg">
                    {searchFields.map((field) => (
                      <th
                        key={`sort-${field.key}`}
                        scope="col"
                        aria-sort={getSortAriaLabel(field.key as keyof User)}
                        className="p-2 md:p-3 text-center text-orange-300 font-bold text-sm md:text-base"
                      >
                        <button
                          onClick={() => requestSort(field.key as keyof User)}
                          className="w-full flex items-center justify-center gap-1 hover:text-white focus:outline-none focus:ring-2 focus:ring-orange-400 rounded cursor-pointer"
                          aria-label={`${t("Sort by")} ${t(field.label)}`}
                          type="button"
                        >
                          {t(field.label)}
                          {sortConfig?.key === field.key && (
                            <span aria-hidden="true">
                              {sortConfig.direction === "asc" ? "↑" : "↓"}
                            </span>
                          )}
                        </button>
                      </th>
                    ))}
                    <th scope="col" className="p-2 md:p-3 w-12">
                      <span className="sr-only">{t("Actions")}</span>
                    </th>
                  </tr>
                </thead>
                <tbody>
                  {filteredUsers.length > 0 ? (
                    filteredUsers.map((user) => (
                      <tr
                        key={user.id}
                        className="bg-orange-800 rounded-lg mb-2 hover:bg-orange-700 transition-colors"
                      >
                        <td className="p-2 md:p-3 text-center text-white text-sm md:text-base">
                          {user.registerDate}
                        </td>
                        <td className="p-2 md:p-3 text-center text-white font-bold text-sm md:text-base">
                          {user.name}
                        </td>
                        <td className="p-2 md:p-3 text-center text-white font-bold text-sm md:text-base">
                          {user.lastname}
                        </td>
                        <td className="p-2 md:p-3 text-center text-white text-sm md:text-base">
                          {user.email}
                        </td>
                        <td className="p-2 md:p-3 text-center">
                          <label htmlFor={`user-role-${user.id}`} className="sr-only">
                            {t("Role for")} {user.name} {user.lastname}
                          </label>
                          <select
                            id={`user-role-${user.id}`}
                            value={user.role}
                            onChange={(e) => {
                              setPendingRoleChange({ userId: user.id, newRole: e.target.value });
                              setShowRoleConfirm(true);
                            }}
                            className="bg-orange-900 text-orange-100 p-1 border border-orange-600 rounded cursor-pointer focus:outline-none focus:ring-2 focus:ring-orange-400"
                          >
                            <option value="user">{t("User")}</option>
                            <option value="admin">{t("Admin")}</option>
                          </select>
                        </td>
                        <td className="p-2 md:p-3 text-center">
                          <TrashButton
                            ariaLabel={`${t("Delete user")} ${user.name} ${user.lastname}`}
                            onButtonClick={() => {
                              setUserToDelete(user.id);
                              setShowDeleteConfirm(true);
                            }}
                          />
                        </td>
                      </tr>
                    ))
                  ) : (
                    <tr>
                      <td
                        colSpan={searchFields.length + 1}
                        className="text-orange-300 text-center py-10"
                      >
                        {t("No users found.")}
                      </td>
                    </tr>
                  )}
                </tbody>
              </table>
            )}
          </div>

          {totalPages > 1 && (
            <nav
              aria-label={t("Pagination")}
              className="flex justify-center items-center gap-4 mt-2 p-2 bg-orange-900 rounded-lg"
            >
              <button
                disabled={currentPage === 1}
                onClick={() => setCurrentPage((prev) => Math.max(prev - 1, 1))}
                aria-label={t("Go to previous page")}
                className="px-3 py-1 bg-orange-700 text-white rounded disabled:opacity-50 disabled:cursor-not-allowed hover:bg-orange-600 cursor-pointer focus:outline-none focus:ring-2 focus:ring-orange-400"
                type="button"
              >
                {t("Previous")}
              </button>
              <span
                ref={paginationStatusRef}
                aria-live="polite"
                aria-atomic="true"
                className="text-orange-200"
              >
                {t("Page")} {currentPage} {t("of")} {totalPages}
              </span>
              <button
                disabled={currentPage === totalPages}
                onClick={() => setCurrentPage((prev) => Math.min(prev + 1, totalPages))}
                aria-label={t("Go to next page")}
                className="px-3 py-1 bg-orange-700 text-white rounded disabled:opacity-50 disabled:cursor-not-allowed hover:bg-orange-600 cursor-pointer focus:outline-none focus:ring-2 focus:ring-orange-400"
                type="button"
              >
                {t("Next")}
              </button>
            </nav>
          )}
        </section>
      </div>

      <ConfirmModal
        isOpen={showDeleteConfirm}
        title={t("Delete User")}
        message={t("Are you sure you want to delete this user? This action cannot be undone.")}
        confirmLabel={t("Delete")}
        cancelLabel={t("Cancel")}
        isDangerous={true}
        isLoading={isDeleting}
        onConfirm={handleConfirmDelete}
        onCancel={() => {
          setShowDeleteConfirm(false);
          setUserToDelete(null);
        }}
      />

      <ConfirmModal
        isOpen={showRoleConfirm}
        title={t("Change Role")}
        message={
          t("Are you sure you want to change this user's role to") +
          " " +
          t(pendingRoleChange?.newRole === "admin" ? "Admin" : "User") +
          "?"
        }
        confirmLabel={t("Confirm")}
        cancelLabel={t("Cancel")}
        isDangerous={pendingRoleChange?.newRole === "admin"}
        isLoading={false}
        onConfirm={handleConfirmRoleChange}
        onCancel={() => {
          setShowRoleConfirm(false);
          setPendingRoleChange(null);
        }}
      />
    </main>
  );
}
