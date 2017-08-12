# Copyright 1999-2011 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: Exp $

DESCRIPTION="ssh forced command authenticator"
HOMEPAGE="https://github.com/11001100/authprogs"
EGIT_REPO_URI="https://github.com/11001100/authprogs.git"

inherit git

LICENSE="BSD"
SLOT="0"
KEYWORDS="x86 amd64"
IUSE=""

RDEPEND="virtual/ssh"
DEPEND="${RDEPEND}"
RESTRICT="mirror"
S="${WORKDIR}/authprogs"

src_compile() {
	emake || die
}

src_install() {
	dobin "${WORKDIR}/authprogs/src/authprogs"
}
