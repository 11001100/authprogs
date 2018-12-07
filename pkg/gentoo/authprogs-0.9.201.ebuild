# Copyright 1999-2018 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2

EAPI=6

DESCRIPTION="ssh forced command authenticator"
HOMEPAGE="https://sourceforge.net/projects/authprogs/ https://github.com/11001100/authprogs"

if [[ ${PV} == 9999 ]]; then
	#inherit subversion
	#ESVN_REPO_URI="svn://svn.code.sf.net/p/authprogs/code/trunk"
	inherit git-r3
	EGIT_REPO_URI="https://github.com/11001100/${PN}.git"
	KEYWORDS="~amd64 ~x86"
else
	#SRC_URI="mirror://sourceforge/${PN}/${P}.tar.bz2"
	SRC_URI="https://github.com/11001100/${PN}/archive/${PV}.tar.gz -> ${P}.tar.gz"
	KEYWORDS="amd64 x86"
fi

LICENSE="BSD"
SLOT="0"
IUSE=""

RDEPEND="virtual/ssh"
DEPEND="${RDEPEND}"
RESTRICT="mirror"

src_compile() {
	emake || die
}

src_install() {
	dobin "${S}/src/authprogs"
}
